import psycopg2
from flask import Flask, render_template, request

app = Flask(__name__)

connect = psycopg2.connect("dbname=deliverseoul user=postgres password=1823")
cur = connect.cursor()


@app.route('/')
def main():
    return render_template("main.html")


@app.route('/print_restaurant', methods=['POST'])
def print_restaurant():
    phone_number = request.form['phone_number']
    street_number = request.form['street_number']
    street_name = request.form['street_name']
    apt_number = request.form['apt_number']
    city = request.form['city']
    state = request.form['state']

    cur.execute("insert into customer values({});".format(phone_number))
    cur.execute("insert into address values({},'{}',{},'{}','{}');"
                .format(street_number, street_name, apt_number, city, state))
    cur.execute("insert into belongs values({},{},'{}',{},'{}','{}');"
                .format(phone_number, street_number, street_name, apt_number, city, state))

    connect.commit()

    cur.execute("select name, category, rate, tip, expected_time from restaurant where restaurant_id <> 0;")
    result = cur.fetchall()
    return render_template("restaurant.html", phone_number=phone_number, restaurants=result)


@app.route('/print_menu', methods=['POST'])
def print_menu():
    phone_number = request.form['phone_number']
    restaurant_name = request.form['restaurant']

    cur.execute("select restaurant_id from restaurant where name = '{}';".format(restaurant_name))
    restaurant = cur.fetchall()
    restaurant_id = restaurant[0][0]

    cur.execute("select menu.name, cost from menu, restaurant "
                "where menu.restaurant_id = restaurant.restaurant_id and restaurant.name = '{}';"
                .format(restaurant_name))
    result = cur.fetchall()

    return render_template("menu.html", phone_number=phone_number, restaurant_id=restaurant_id, menus=result)


@app.route('/order_received', methods=['POST'])
def order_received():
    phone_number = request.form['phone_number']
    restaurant_id = request.form['restaurant_id']
    menu1 = request.form['menu1']
    menu2 = request.form['menu2']
    menu3 = request.form['menu3']
    amount1 = request.form['amount1']
    amount2 = request.form['amount2']
    amount3 = request.form['amount3']

    cur.execute("select menu_id from menu where name = '{}';".format(menu1))
    m1_id = cur.fetchall()
    menu1_id = m1_id[0][0]
    cur.execute("select menu_id from menu where name = '{}';".format(menu2))
    m2_id = cur.fetchall()
    menu2_id = m2_id[0][0]
    cur.execute("select menu_id from menu where name = '{}';".format(menu3))
    m3_id = cur.fetchall()
    menu3_id = m3_id[0][0]

    cur.execute("insert into adds values({}, {}, {});".format(phone_number, menu1_id, amount1))
    cur.execute("insert into adds values({}, {}, {});".format(phone_number, menu2_id, amount2))
    cur.execute("insert into adds values({}, {}, {});".format(phone_number, menu3_id, amount3))
    connect.commit()

    cur.execute("with food_expense (menu_id, cost, amount) as (select menu_id, cost, amount "
                "from adds natural join menu where phone_number = {} and restaurant_id = {}), "
                "delivery_fee (value) as (select tip from restaurant where restaurant_id = {}), "
                "sum_expense (value) as (select sum(cost * amount) from food_expense) "
                "select sum_expense.value + delivery_fee.value from sum_expense, delivery_fee;"
                .format(phone_number, restaurant_id, restaurant_id))
    t_cost = cur.fetchall()
    total_cost = t_cost[0][0]

    cur.execute("select expected_time from restaurant where restaurant_id = {};".format(restaurant_id))
    e_time = cur.fetchall()
    expected_time = e_time[0][0]

    cur.execute("with area_load (id, num, ld) as (select carrier_id, phone_number, load from carrier "
                "where responsible_area = (select street_name from restaurant where restaurant_id = {})), "
                "min_load (value) as (select min(ld) from area_load) select num from area_load, min_load "
                "where ld = value and id <= all (select id from area_load, min_load where ld = value);"
                .format(restaurant_id))
    carrier = cur.fetchall()
    carrier_pn = carrier[0][0]

    cur.execute("select carrier_id from carrier where phone_number = {}".format(carrier_pn))
    c_id = cur.fetchall()
    carrier_id = c_id[0][0]

    cur.execute("update carrier set load = load + 1 where carrier_id = {}".format(carrier_id))
    connect.commit()

    cur.execute("select max(id) from order_")
    temp = cur.fetchall()
    temp_id = temp[0][0]
    temp_id += 1

    cur.execute("insert into order_ values({}, {}, {}, {}, {})"
                .format(temp_id, phone_number, restaurant_id, carrier_id, total_cost))
    cur.execute("delete from adds where phone_number = {}".format(phone_number))
    connect.commit()

    return render_template("order.html", total_cost=total_cost, expected_time=expected_time, contact=carrier_pn)


if __name__ == '__main__':
    app.run()

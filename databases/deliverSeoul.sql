drop table order_;
drop table adds;
drop table belongs;
drop table menu;
drop table carrier;
drop table restaurant;
drop table address;
drop table customer;

create table customer(phone_number numeric(11,0), primary key (phone_number));
create table address(street_number int, street_name varchar(50), apt_number int, city varchar(50), state varchar(50), primary key (street_number, street_name, apt_number, city, state));
create table restaurant(restaurant_id numeric(8,0), name varchar(50), category varchar(50), rate numeric(1,0), tip int, expected_time int, street_number int, street_name varchar(50), apt_number int, city varchar(50), state varchar(50), 
		telephone_number numeric(11,0), primary key(restaurant_id), check(rate <=5));
create table carrier(carrier_id numeric(8,0), phone_number numeric(11,0), load numeric(2,0), responsible_area varchar(50), primary key(carrier_id));
create table menu(menu_id numeric(10,0), restaurant_id numeric(8,0), name varchar(50), cost int, primary key(menu_id), foreign key (restaurant_id) references restaurant);
create table belongs(phone_number numeric(11,0), street_number int, street_name varchar(50), apt_number int, city varchar(50), state varchar(50), primary key (phone_number, street_number, street_name, apt_number, city, state), 
		foreign key (phone_number) references customer, foreign key (street_number, street_name, apt_number, city, state) references address);
create table adds(phone_number numeric(11,0), menu_id numeric(10,0), amount numeric(2,0), primary key (phone_number, menu_id), foreign key (phone_number) references customer, foreign key (menu_id) references menu,
		check(amount <= 10));
create table order_(id numeric(8,0), phone_number numeric(11,0), restaurant_id numeric(8,0), carrier_id numeric(8,0), payment_amount int, primary key(id), foreign key (phone_number) references customer,
		foreign key (restaurant_id) references restaurant, foreign key (carrier_id) references carrier);

insert into customer values (00000000000);

insert into restaurant values (00000000, null, null, null, null, null, null, null, null, null, null, null);
insert into restaurant values (52750001, 'Yil Yil Hyang', 'Chinese', 3, 2000, 30, 99, 'Olympic-ro', 3, 'Seoul', 'Republic of Korea', 01052071823);
insert into restaurant values (52750002, 'Downtowner', 'fast food', 5, 3000, 40, 135, 'Olympic-ro', 5, 'Seoul', 'Republic of Korea', 01004120322);
insert into restaurant values (52750003, 'Pizza Never Sleeps', 'pizza', 3, 2500, 50, 101, 'Olympic-ro', 7, 'Seoul', 'Republic of Korea', 01009130412);
insert into restaurant values (78250001, 'Delicious Snack', 'school food', 4, 3000, 30, 37, 'Teheran-ro', 45, 'Seoul', 'Republic of Korea', 01010090620);
insert into restaurant values (78250002, 'Gamsung Taco', 'Mexican', 5, 3000, 60, 43, 'Teheran-ro', 17, 'Seoul', 'Republic of Korea', 01004260412);
insert into restaurant values (78250003, 'Useung Restaurant', 'Korean', 5, 2500, 40, 17, 'Teheran-ro', 6, 'Seoul', 'Republic of Korea', 01003200419);
insert into restaurant values (25750001, 'Eulji Darak', 'Italian', 4, 3000, 60, 21, 'Eulji-ro', 14, 'Seoul', 'Republic of Korea', 01026753200);
insert into restaurant values (25750002, 'George Seoul', 'dessert', 4, 3500, 40, 35, 'Eulji-ro', 25, 'Seoul', 'Republic of Korea', 01020210602);
insert into restaurant values (25750003, 'Manseon Hof', 'chicken', 3, 2000, 70, 72, 'Eulji-ro', 9, 'Seoul', 'Republic of Korea', 01012345678);

insert into carrier values (00000000, null, null, null);
insert into carrier values (52751101, 01052751101, 3, 'Olympic-ro');
insert into carrier values (52751102, 01011025275, 2, 'Olympic-ro');
insert into carrier values (52751103, 01006020749, 1, 'Olympic-ro');
insert into carrier values (78251101, 01078251101, 4, 'Teheran-ro');
insert into carrier values (78251102, 01020115287, 5, 'Teheran-ro');
insert into carrier values (78251103, 01007517825, 6, 'Teheran-ro');
insert into carrier values (25751101, 01025751101, 6, 'Eulji-ro');
insert into carrier values (25751102, 01035007895, 7, 'Eulji-ro');
insert into carrier values (25751103, 01034829493, 8, 'Eulji-ro');

insert into menu values (5275000101, 52750001, 'Jajangmyeon', 7000);
insert into menu values (5275000102, 52750001, 'Jjambbong', 8000);
insert into menu values (5275000103, 52750001, 'Sweet and Sour Pork', 26000);
insert into menu values (5275000201, 52750002, 'Avocado Burger', 9300);
insert into menu values (5275000202, 52750002, 'Bacon Cheese Burger', 7800);
insert into menu values (5275000203, 52750002, 'Shrimp Burger', 9300);
insert into menu values (5275000301, 52750003, 'Chicken Pizza', 28000);
insert into menu values (5275000302, 52750003, 'Potato Pizza', 26000);
insert into menu values (5275000303, 52750003, 'Pepperoni Pizza', 25000);
insert into menu values (7825000101, 78250001, 'Tteogbokki', 2000);
insert into menu values (7825000102, 78250001, 'Sundae', 2000);
insert into menu values (7825000103, 78250001, 'Tteogkkochi', 3000);
insert into menu values (7825000201, 78250002, 'Grilled Pajita', 38000);
insert into menu values (7825000202, 78250002, 'Taco', 9000);
insert into menu values (7825000203, 78250002, 'Quesadia', 13000);
insert into menu values (7825000301, 78250003, 'Jeyuk Bokkeum', 6000);
insert into menu values (7825000302, 78250003, 'Webfoot Octopus Bokkeum', 7000);
insert into menu values (7825000303, 78250003, 'Bean Paste Stew', 2000);
insert into menu values (2575000101, 25750001, 'Pasta', 15000);
insert into menu values (2575000102, 25750001, 'Omlet Rice', 14000);
insert into menu values (2575000103, 25750001, 'Katsu Sando', 10000);
insert into menu values (2575000201, 25750002, 'Purorong Jelly Soda', 8500);
insert into menu values (2575000202, 25750002, 'Pinkpangpang', 7000);
insert into menu values (2575000203, 25750002, 'Tiramisu', 7000);
insert into menu values (2575000301, 25750003, 'Garlic Chicken', 17000);
insert into menu values (2575000302, 25750003, 'Fried Chicken', 16000);
insert into menu values (2575000303, 25750003, 'Seasoned Spicy Chicken', 17000);

insert into order_ values (00000000, 00000000000, 00000000, 00000000, null);














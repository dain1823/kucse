import re

report = str()
for i in range(10):
    temp = input()
    report += temp
    report += ' '

sreport = report.split()
count_phone = 0
count_card = 0

phone = re.compile('^010\-{1}\d{4}\-{1}\d{4}$')
card = re.compile('^\d{4}\-{1}\d{4}\-{1}\d{4}\-{1}\d{4}$')

for i in range(len(sreport)):
    if phone.search(sreport[i]):
        count_phone += 1
        continue
    if card.search(sreport[i]):
        count_card += 1
        continue

print(str(count_phone) + '\n' + str(count_card))

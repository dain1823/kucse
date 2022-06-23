import re

report = str()
for i in range(10):
    temp = input()
    report += temp
    report += ' '

sreport = report.split()
count_SSN = 0
count_email = 0

SSN28 = re.compile('^(9[8-9]|0[0-1])02(0[1-9]|1\d|2[0-8])\-{1}[1-4]\d{6}$')
SSN29 = re.compile('^0{2}02(0[1-9]|[1-2]\d)\-{1}[1-4]\d{6}$')
SSN30 = re.compile('^(9[8-9]|0[0-1])(04|06|09|11)(0[1-9]|[1-2]\d|30)\-{1}[1-4]\d{6}$')
SSN31 = re.compile('^(9[8-9]|0[0-1])(01|03|05|07|08|10|12)(0[1-9]|[1-2]\d|3[0-1])\-{1}[1-4]\d{6}$')

email = re.compile('^[A-Za-z0-9]+\@{1}[A-Za-z]+\.{1}ac\.{1}kr$')

for i in range(len(sreport)):
    if SSN28.search(sreport[i]):
        count_SSN += 1
        continue
    if SSN29.search(sreport[i]):
        count_SSN += 1
        continue
    if SSN30.search(sreport[i]):
        count_SSN += 1
        continue
    if SSN31.search(sreport[i]):
        count_SSN += 1
        continue
    if email.search(sreport[i]):
        count_email += 1
        continue

print(str(count_SSN) + '\n' + str(count_email))

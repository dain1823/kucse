import re

code = input()
code = code.strip('“”"')
scode = code.split(' ')

A = re.compile('^\.{1}\-{1}$')
B = re.compile('^\-{1}\.{3}$')
C = re.compile('^\-{1}\.{1}\-{1}\.{1}$')
D = re.compile('^\-{1}\.{2}$')
E = re.compile('^\.{1}$')
F = re.compile('^\.{2}\-{1}\.{1}$')
G = re.compile('^\-{2}\.{1}$')
H = re.compile('^\.{4}$')
I = re.compile('^\.{2}$')
J = re.compile('^\.{1}\-{3}$')
K = re.compile('^\-{1}\.{1}\-{1}$')
L = re.compile('^\.{1}\-{1}\.{2}$')
M = re.compile('^\-{2}$')
N = re.compile('^\-{1}\.{1}$')
O = re.compile('^\-{3}$')
P = re.compile('^\.{1}\-{2}\.{1}$')
Q = re.compile('^\-{2}\.{1}\-{1}$')
R = re.compile('^\.{1}\-{1}\.{1}$')
S = re.compile('^\.{3}$')
T = re.compile('^\-{1}$')
U = re.compile('^\.{2}\-{1}$')
V = re.compile('^\.{3}\-{1}$')
W = re.compile('^\.{1}\-{2}$')
X = re.compile('^\-{1}\.{2}\-{1}$')
Y = re.compile('^\-{1}\.{1}\-{2}$')
Z = re.compile('^\-{2}\.{2}$')
_0 = re.compile('^\-{5}$')
_1 = re.compile('^\.{1}\-{4}$')
_2 = re.compile('^\.{2}\-{3}$')
_3 = re.compile('^\.{3}\-{2}$')
_4 = re.compile('^\.{4}\-{1}$')
_5 = re.compile('^\.{5}$')
_6 = re.compile('^\-{1}\.{4}$')
_7 = re.compile('^\-{2}\.{3}$')
_8 = re.compile('^\-{3}\.{2}$')
_9 = re.compile('^\-{4}\.{1}$')
period = re.compile('^\.{1}\-{1}\.{1}\-{1}\.{1}\-{1}$')
comma = re.compile('^\-{2}\.{2}\-{2}$')
qmark = re.compile('^\.{2}\-{2}\.{2}$')
apos = re.compile('^\.{1}\-{4}\.{1}$')
emark = re.compile('^\-{1}\.{1}\-{1}\.{1}\-{2}$')
fslash = re.compile('^\-{1}\.{2}\-{1}\.{1}$')
lpar = re.compile('^\-{1}\.{1}\-{2}\.{1}$')
rpar = re.compile('^\-{1}\.{1}\-{2}\.{1}\-{1}$')
amper = re.compile('^\.{1}\-{1}\.{3}$')
colon = re.compile('^\-{3}\.{3}$')
semic = re.compile('^\-{1}\.{1}\-{1}\.{1}\-{1}\.{1}$')
esign = re.compile('^\-{1}\.{3}\-{1}$')
psign = re.compile('^\.{1}\-{1}\.{1}\-{1}\.{1}$')
hyphen = re.compile('^\-{1}\.{4}\-{1}$')
underb = re.compile('^\.{2}\-{2}\.{1}\-{1}$')
quota = re.compile('^\.{1}\-{1}\.{2}\-{1}\.{1}$')
dollar = re.compile('^\.{3}\-{1}\.{2}\-{1}$')
atmark = re.compile('^\.{1}\-{2}\.{1}\-{1}\.{1}$')
udqmark = re.compile('^\.{2}\-{1}\.{1}\-{1}$')
udemark = re.compile('^\-{2}\.{3}\-{1}$')

for i in range(len(scode)):
    if A.search(scode[i]):
        scode[i] = 'A'
        continue
    if B.search(scode[i]):
        scode[i] = 'B'
        continue
    if C.search(scode[i]):
        scode[i] = 'C'
        continue
    if D.search(scode[i]):
        scode[i] = 'D'
        continue
    if E.search(scode[i]):
        scode[i] = 'E'
        continue
    if F.search(scode[i]):
        scode[i] = 'F'
        continue
    if G.search(scode[i]):
        scode[i] = 'G'
        continue
    if H.search(scode[i]):
        scode[i] = 'H'
        continue
    if I.search(scode[i]):
        scode[i] = 'I'
        continue
    if J.search(scode[i]):
        scode[i] = 'J'
        continue
    if K.search(scode[i]):
        scode[i] = 'K'
        continue
    if L.search(scode[i]):
        scode[i] = 'L'
        continue
    if M.search(scode[i]):
        scode[i] = 'M'
        continue
    if N.search(scode[i]):
        scode[i] = 'N'
        continue
    if O.search(scode[i]):
        scode[i] = 'O'
        continue
    if P.search(scode[i]):
        scode[i] = 'P'
        continue
    if Q.search(scode[i]):
        scode[i] = 'Q'
        continue
    if R.search(scode[i]):
        scode[i] = 'R'
        continue
    if S.search(scode[i]):
        scode[i] = 'S'
        continue
    if T.search(scode[i]):
        scode[i] = 'T'
        continue
    if U.search(scode[i]):
        scode[i] = 'U'
        continue
    if V.search(scode[i]):
        scode[i] = 'V'
        continue
    if W.search(scode[i]):
        scode[i] = 'W'
        continue
    if X.search(scode[i]):
        scode[i] = 'X'
        continue
    if Y.search(scode[i]):
        scode[i] = 'Y'
        continue
    if Z.search(scode[i]):
        scode[i] = 'Z'
        continue
    if _0.search(scode[i]):
        scode[i] = '0'
        continue
    if _1.search(scode[i]):
        scode[i] = '1'
        continue
    if _2.search(scode[i]):
        scode[i] = '2'
        continue
    if _3.search(scode[i]):
        scode[i] = '3'
        continue
    if _4.search(scode[i]):
        scode[i] = '4'
        continue
    if _5.search(scode[i]):
        scode[i] = '5'
        continue
    if _6.search(scode[i]):
        scode[i] = '6'
        continue
    if _7.search(scode[i]):
        scode[i] = '7'
        continue
    if _8.search(scode[i]):
        scode[i] = '8'
        continue
    if _9.search(scode[i]):
        scode[i] = '9'
        continue
    if period.search(scode[i]):
        scode[i] = '.'
        continue
    if comma.search(scode[i]):
        scode[i] = ','
        continue
    if qmark.search(scode[i]):
        scode[i] = '?'
        continue
    if apos.search(scode[i]):
        scode[i] = "'"
        continue
    if emark.search(scode[i]):
        scode[i] = '!'
        continue
    if fslash.search(scode[i]):
        scode[i] = '/'
        continue
    if lpar.search(scode[i]):
        scode[i] = '('
        continue
    if rpar.search(scode[i]):
        scode[i] = ')'
        continue
    if amper.search(scode[i]):
        scode[i] = '&'
        continue
    if colon.search(scode[i]):
        scode[i] = ':'
        continue
    if semic.search(scode[i]):
        scode[i] = ';'
        continue
    if esign.search(scode[i]):
        scode[i] = '='
        continue
    if psign.search(scode[i]):
        scode[i] = '+'
        continue
    if hyphen.search(scode[i]):
        scode[i] = '-'
        continue
    if underb.search(scode[i]):
        scode[i] = '_'
        continue
    if quota.search(scode[i]):
        scode[i] = '"'
        continue
    if dollar.search(scode[i]):
        scode[i] = '$'
        continue
    if atmark.search(scode[i]):
        scode[i] = '@'
        continue
    if udqmark.search(scode[i]):
        scode[i] = '¿'
        continue
    if udemark.search(scode[i]):
        scode[i] = '¡'
        continue

URL = ''.join(scode)

print('“' + URL + '”')

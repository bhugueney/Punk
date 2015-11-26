# https://soundcloud.com/maxtuno/universal-number-theory-string-quartet-n-1

from music21 import *
from sage.all_cmdline import *


def riverian_polynomial(n, b, m):
    Rz.<z> = PolynomialRing(IntegerModRing(m))
    return Rz(ZZ(n).digits(b))


def make_part(ps, ds, origin):
    part = stream.Part()
    m = stream.Measure()
    for pit, dur in zip(map(int, ps), map(float, ds)):
        m.append(note.Note(midi=pit + origin, quarterLength=dur))
    part.append(m)
    return part


ms = [riverian_polynomial(11, 5, 24)(z=p) for p in range(2^8 - 1)]
ns = [mod(d, ceil(32 * sin(d))) for d in ms]

ps1 = [riverian_polynomial(7, 4, 24)(z=p) for p in range(2^8 - 1)]
ds1 = [mod(d, ceil(16 * sin(d))) for d in ps1]

ps2 = [riverian_polynomial(5, 3, 24)(z=p) for p in range(2^8 - 1)]
ds2 = [mod(d, ceil(8 * sin(d))) for d in ps2]

xs = [riverian_polynomial(3, 2, 24)(z=p) for p in range(2^8 - 1)]
ys = [mod(d, ceil(4 * sin(d))) for d in xs]


score = stream.Score()
score.insert(0, make_part(ms, ns, 60))
score.insert(0, make_part(ps1, ds1, 56))
score.insert(0, make_part(ps2, ds2, 48))
score.insert(0, make_part(xs, ys, 36))
score.show('midi')

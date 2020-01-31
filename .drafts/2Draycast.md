Let there be a segment AB
Let there be a vector î
^b is the vector going from A to B

Within the ray AB: 
Y = (x - A.x) * (^b.y/^b.x) + A.y
Test:
Y(2.5) = (x - A.x) * (^b.y/^b.x) + A.y
= (2.5 - 1) * -2/3 + 3
= 1.5 * -2/3 +3
= 3/2 * -2/3 + 3
= -1 + 3
= 2
OK

Within the ray î:
y = x * î.y/î.x

The rays AB and î cross at:
x * î.y/î.x = (x - A.x) * ^b.y/^b.x + A.y
x * î.y/î.x = x * ^b.y/^b.x - A.x * ^b.y/^b.x + A.y
x * î.y/î.x - x * ^b.y/^b.x = -A.x * ^b.y/^b.x + A.y
x *(î.y/î.x - ^b.y/^b.x) = -A.x * ^b.y/^b.x + A.y
x = (-A.x * ^b.y/^b.x + A.y) / (î.y/î.x - ^b.y/^b.x)
x = (-A.x * ^b.y/^b.x + A.y) / (^b.x*î.y/î.x - ^b.y)/^b.x
x = (-A.x * ^b.y/^b.x + A.y) * ^b.x / (^b.x*î.y/î.x - ^b.y)
x = (-A.x * ^b.y + A.y * ^b.x) / (^b.x*î.y/î.x - ^b.y)
x = (-A.x * ^b.y + A.y * ^b.x) / (^b.x*î.y - ^b.y*î.x)/î.x
x = (-A.x * ^b.y + A.y * ^b.x) * î.x / (^b.x*î.y - ^b.y*î.x)

Test:
x = (-A.x * ^b.y + A.y * ^b.x) * î.x / (^b.x*î.y - ^b.y*î.x)
= (-1 * -2 + 3 * 3) * 1 / (3 * 1 - -2 * 1)
= (2 + 9) / (3 + 2)
= 11 / 5
= 2.2
OK

x = (-A.x * ^b.y + A.y * ^b.x) * î.x / (^b.x*î.y - ^b.y*î.x)
= (-1 * -2 + 3 * 3) * 0.5 / (3 * 1.5 - -2 * 0.5)
= (2 + 9) * 0.5 / (4.5  + 1)
= 11 * 0.5 / 5.5
= 11 * 0.5 / 5.5
= 5.5 / 5.5
= 1
OK
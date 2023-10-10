a) void assign_to_point ( struct point p, int a, int b) {p.x=a; p.y=b;}  - нельзя

b) void assign_to_point ( struct point ∗p, int a, int b) {(∗p).x=a; (∗p).y=b;}   - можно

c) void assign_to_point ( struct point ∗p, int a, int b) {∗p.x=a; ∗p.y=b;}  - нельзя

d) void assign_to_point ( struct point ∗p, int a, int b) {p->x=a; p->y=b;}  - можно

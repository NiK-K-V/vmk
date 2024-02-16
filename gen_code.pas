program pon;
const n=10;
type genome = string[14];
var	i,m_num:integer;
	ex:boolean;
	res_1,res_2,res_3,res_4,res_5,res_6,res_7,res_8,res_9,res_10,stop_point,control,pred_control,maxx:real;
	crtr_1,crtr_2,crtr_3,crtr_4,crtr_5,crtr_6,crtr_7,crtr_8,crtr_9,crtr_10:genome;
	c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,counter:integer;
	x1,x2,x3,x4,x5,x6,x7,x8,x9,x10:real;

function max(x1,x2,x3,x4,x5,x6,x7,x8,x9,x10:real):real;
var arr: array [1..10] of real;
	i,j:integer;
	b:real;
begin
arr[1]:=x1;
arr[2]:=x2;
arr[3]:=x3;
arr[4]:=x4;
arr[5]:=x5;
arr[6]:=x6;
arr[7]:=x7;
arr[8]:=x8;
arr[9]:=x9;
arr[10]:=x10;
for i:=10 downto 2 do 
    begin
	for j:=1 to i-1 do 
	    begin
		if arr[j]>arr[j+1] then 
		    begin
			b:=arr[j];
			arr[j]:=arr[j+1];
			arr[j+1]:=b;
		    end;
	    end;
    end;
max:=arr[10];
end;

function degree(x,p:integer):integer;
var s,i:integer;
begin
if p=0 then
    degree:=1;
s:=x;
for i:=2 to p do
	x:=x*s;
if p<>0 then
    degree:=x;
end;

function build_genome(x:integer):genome;
var s:genome;
begin
s:='';
while x>0 do
    begin
	if x mod 2 = 1 then
		s := '1' + s
	else
		s := '0' + s;
	x := x div 2;
	end;
while ord(s[0])<14 do
	s:= '0'+s;
build_genome:=s;
end;

function build_number_by_genome(x:genome):integer;
var s,i:integer;
begin
s:=0;
for i:=1 to 14 do 
    begin
	if x[i] = '1' then
		s := s+degree(2,14-i)
	end;
build_number_by_genome:=s;
end;

function get_x_by_byte(x:integer):real;
begin
get_x_by_byte:=(4/16384)*x;
end;

function func(x:real):real;
begin
func:=x*(x-1.1)*(x-1.1)*(x-1.1)*(x-1.1)*(x-1.1)*(x-1.2)*(x-1.2)*(x-1.2)*(x-1.2)
    *(x-1.3)*(x-1.3)*(x-1.3)*cos(x+100);
end;

procedure mutation(var x:genome);  {reverse}
var s:char;
	i:integer;
	bytes:byte;
begin
bytes:=14;
for i:=2 to (bytes div 2) do 
    begin
	s := x[i];
	x[i]:=x[bytes-i+2];
	x[bytes-i+2]:=s;
	end;
end;

procedure next_gen(var x1,x2:genome);
var p1,p2,p3,p4,f1,f2,f3,f4:genome;
	i:integer;
begin
p1:='';
p2:='';
p3:='';
p4:='';
f1:='';
f2:='';
f3:='';
f4:='';
for i:=1 to 7 do 
    begin
	p1:=p1 + x1[i];
	f1:=f1 + x2[i];
	end;
for i:=8 to 14 do 
    begin
	p2:=p2 + x1[i];
	f2:=f2 + x2[i];
	end;
x1:=p1 + f2;
x2:=f1 + p2;
end;

procedure proportional_selection(var c1,c2,c3,c4,c5,c6,c7,c8,c9,c10:genome);
var b,c,f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,gp:real;
	arr : array [1..10,1..2] of real;
	i,j:integer;
	r1,r2,r3,r4:genome;
	num1,num2,num3,num4:integer;
	
begin
f1:=func(get_x_by_byte(build_number_by_genome(c1)));
f2:=func(get_x_by_byte(build_number_by_genome(c2)));
f3:=func(get_x_by_byte(build_number_by_genome(c3)));
f4:=func(get_x_by_byte(build_number_by_genome(c4)));
f5:=func(get_x_by_byte(build_number_by_genome(c4)));
f6:=func(get_x_by_byte(build_number_by_genome(c5)));
f7:=func(get_x_by_byte(build_number_by_genome(c7)));
f8:=func(get_x_by_byte(build_number_by_genome(c8)));
f9:=func(get_x_by_byte(build_number_by_genome(c9)));
f10:=func(get_x_by_byte(build_number_by_genome(c10)));

gp := (f1+f2+f3+f4+f5+f6+f7+f8+f9+f10)/10;

p1:=0;
p2:=0;
p3:=0;
p4:=0;
p5:=0;
p6:=0;
p7:=0;
p8:=0;
p9:=0;
p10:=0;

p1 := f1;
p2 := f2;
p3 := f3;
p4 := f4;
p5 := f5;
p6 := f6;
p7 := f7;
p8 := f8;
p9 := f9;
p10 := f10;

arr[1][1]:=p1;
arr[1][2]:=1;
arr[2][1]:=p2;
arr[2][2]:=2;
arr[3][1]:=p3;
arr[3][2]:=3;
arr[4][1]:=p4;
arr[4][2]:=4;
arr[5][1]:=p5;
arr[5][2]:=5;
arr[6][1]:=p6;
arr[6][2]:=6;
arr[7][1]:=p7;
arr[7][2]:=7;
arr[8][1]:=p8;
arr[8][2]:=8;
arr[9][1]:=p9;
arr[9][2]:=9;
arr[10][1]:=p10;
arr[10][2]:=10;

for i:=10 downto 2 do
    begin
	for j:=1 to i-1 do 
	    begin
		if arr[j][1]>arr[j+1][1] then 
		    begin
			b:=arr[j][1];
			c:=arr[j][2];
			arr[j][1]:=arr[j+1][1];
			arr[j][2]:=arr[j+1][2];
			arr[j+1][1]:=b;
			arr[j+1][2]:=c;
		    end;
	    end;
    end;

num1:=round(arr[10][2]);
num2:=round(arr[9][2]);
num3:=round(arr[8][2]);
num4:=round(arr[7][2]);
case num1 of 
	1: r1:=c1;
	2: r1:=c2;
	3: r1:=c3;
	4: r1:=c4;
	5: r1:=c5;
	6: r1:=c6;
	7: r1:=c7;
	8: r1:=c8;
	9: r1:=c9;
	10: r1:=c10;
end;
case num2 of 
	1: r2:=c1;
	2: r2:=c2;
	3: r2:=c3;
	4: r2:=c4;
	5: r2:=c5;
	6: r2:=c6;
	7: r2:=c7;
	8: r2:=c8;
	9: r2:=c9;
	10: r2:=c10;
end;
case num3 of 
	1: r3:=c1;
	2: r3:=c2;
	3: r3:=c3;
	4: r3:=c4;
	5: r3:=c5;
	6: r3:=c6;
	7: r3:=c7;
	8: r3:=c8;
	9: r3:=c9;
	10: r3:=c10;
end;
case num4 of 
	1: r4:=c1;
	2: r4:=c2;
	3: r4:=c3;
	4: r4:=c4;
	5: r4:=c5;
	6: r4:=c6;
	7: r4:=c7;
	8: r4:=c8;
	9: r4:=c9;
	10: r4:=c10;
end;
c1:=r1;
c2:=r2;
c3:=r1;
c4:=r3;
c5:=r1;
c6:=r4;
c7:=r2;
c8:=r3;
c9:=r2;
c10:=r4;
end;

begin
ex := true;
control:=0;

randomize;

c1:=random(16384);
c2:=random(16384);
c3:=random(16384);
c4:=random(16384);
c5:=random(16384);
c6:=random(16384);
c7:=random(16384);
c8:=random(16384);
c9:=random(16384);
c10:=random(16384);

crtr_1 := build_genome(c1);
crtr_2 := build_genome(c2);
crtr_3 := build_genome(c3);
crtr_4 := build_genome(c4);
crtr_5 := build_genome(c5);
crtr_6 := build_genome(c6);
crtr_7 := build_genome(c7);
crtr_8 := build_genome(c8);
crtr_9 := build_genome(c9);
crtr_10 := build_genome(c10);
i:=0; 
counter:=0;
writeln;

{stop_point:=;}
pred_control:=0;
while (i<=10) and (counter<5) and (ex) do 
    begin
	x1:=get_x_by_byte(build_number_by_genome(crtr_1));
	x2:=get_x_by_byte(build_number_by_genome(crtr_2));
	x3:=get_x_by_byte(build_number_by_genome(crtr_3));
	x4:=get_x_by_byte(build_number_by_genome(crtr_4));
	x5:=get_x_by_byte(build_number_by_genome(crtr_5));
	x6:=get_x_by_byte(build_number_by_genome(crtr_6));
	x7:=get_x_by_byte(build_number_by_genome(crtr_7));
	x8:=get_x_by_byte(build_number_by_genome(crtr_8));
	x9:=get_x_by_byte(build_number_by_genome(crtr_9));
	x10:=get_x_by_byte(build_number_by_genome(crtr_10));
	res_1:=func(x1);
	res_2:=func(x2);
	res_3:=func(x3);
	res_4:=func(x4);
	res_5:=func(x5);
	res_6:=func(x6);
	res_7:=func(x7);
	res_8:=func(x8);
	res_9:=func(x9);
	res_10:=func(x10);
	{writeln(x1:2:5,' ',res_1:2:5);
	writeln;
	writeln(x2:2:5,' ',res_2:2:5);
	writeln;
	writeln(x3:2:5,' ',res_3:2:5);
	writeln;
	writeln(x4:2:5,' ',res_4:2:5);
	writeln;
	writeln(x5:2:5,' ',res_5:2:5);
	writeln;
	writeln(x6:2:5,' ',res_6:2:5);
	writeln;
	writeln(x7:2:5,' ',res_7:2:5);
	writeln;
	writeln(x8:2:5,' ',res_8:2:5);
	writeln;
	writeln(x9:2:5,' ',res_9:2:5);
	writeln;
	writeln(x10:2:5,' ',res_10:2:5);
	writeln;}
	control := max(res_1,res_2,res_3,res_4,res_5,res_6,res_7,res_8,res_9,res_10);
	if control=res_1 then
	    maxx:=x1;
	if control=res_2 then
	    maxx:=x2;
	if control=res_3 then
	    maxx:=x3;
	if control=res_4 then
	    maxx:=x4;
	if control=res_5 then
	    maxx:=x5;
	if control=res_6 then
	    maxx:=x6;
	if control=res_7 then
	    maxx:=x7;
    if control=res_8 then
	    maxx:=x8;
	if control=res_9 then
	    maxx:=x9;
	if control=res_10 then
	    maxx:=x10;
	
	if control <= pred_control then
		counter := counter + 1;
	{writeln('Текущий результат:           ',control:2:5);
	writeln('Примерная абсцисса точки:    ',maxx:2:5);
	writeln('Номер ухудшения:             ',counter);
	writeln('Номер итерации:              ', i);
	writeln;}
	i:=i+1;
    pred_control:=control;
	
    proportional_selection(crtr_1,crtr_2,crtr_3,crtr_4,crtr_5,crtr_6,crtr_7,crtr_8,crtr_9,crtr_10);
	next_gen(crtr_1,crtr_2);
	next_gen(crtr_3,crtr_4);
	next_gen(crtr_5,crtr_6);
	next_gen(crtr_7,crtr_8);
	next_gen(crtr_9,crtr_10);
	
	m_num:=random(11);
	case m_num of
		1:mutation(crtr_1);
		2:mutation(crtr_2);
		3:mutation(crtr_3);
		4:mutation(crtr_4);
		5:mutation(crtr_5);
		6:mutation(crtr_6);
		7:mutation(crtr_7);
		8:mutation(crtr_8);
		9:mutation(crtr_9);
		10:mutation(crtr_10);
	end;
	
	end;

writeln('Результат:           ',control:2:5);
writeln('Примерная абсцисса:    ',maxx:2:5);
writeln('Номер ухудшения:             ',counter);
writeln('Номер итерации:              ', i);
end.
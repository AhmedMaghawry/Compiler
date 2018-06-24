.source code.txt
.class public test
.super java/lang/Object

.method public <init>()V
aload_0
invokenonvirtual java/lang/Object/<init>()V
return
.end method

.method public static main([Ljava/lang/String;)V
.limit locals 100
.limit stack 100
.line 1
iconst_0
istore 1
Lable0:
ldc 0
istore 1
Lable1:
Lable2:
Lable3:
iload 1
ldc 5
if_icmplt Lable4
goto Lable5
Lable4:
iload 1
ldc 1
iadd
istore 1
goto Lable3
Lable5:
iconst_0
istore 2
Lable6:
iload 1
istore 2
Lable7:
iload 2
ldc 5
if_icmpeq Lable8
goto Lable9
Lable8:
iload 1
ldc 3
imul
istore 2
goto Lable10
Lable9:
iload 1
ldc 3
iadd
istore 2
Lable10:
return
.end method

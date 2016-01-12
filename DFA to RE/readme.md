# DFA转换到RE

## 名词解释

### DFA

> Deterministic Finite Automaton

### RE

> Regular Expression

## 编译

```
make
```

## 输入

```
状态数 转移数
转移1 转移2 ...
...
转移1 转移2 ...
初始状态
终止状态
```

### 示例输入

```
6 2
D B
E C
F A
A E
B F
C D
A
D
```

## 运行

```
./transform
```

如果输入保存在`input.txt`中，并且希望输出到`output.txt`中，则使用

```
make expression
```
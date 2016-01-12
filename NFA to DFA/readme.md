# NFA转换至DFA

## 名词解释

### NFA

> Non-deterministic Finite Automaton

### DFA

> Deterministic Finite Automaton

## 编译

```
make transform
```

## 输入

```
状态数 转移数
转移1 转移2 ...
...
转移1 转移2 ...
初始状态（多个）
终止状态（多个）
```

### 示例输入

```
4 2
A AB
C C
D D
0 0
A
D
```

## 运行

### 转换到*eps*图像

```
make graph
```

### 转换成\\(\LaTeX\\)表格

```
make table
```

## 清空目录

```
make clean
```
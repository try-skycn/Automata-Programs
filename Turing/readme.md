# Turing Machine

## 编译

```
make turing
```

## 运行

```
make
```

或者

```
./turing [-t<间隔时间>] [-h]
```

参数`-t`用于表示两步之间显示间隔的时间（单位是微秒，`1秒=1 000 000微秒`）。

使用参数`-h`表示每一步刷新使用`clear`命令清空终端（这种方式清空终端，终端中会保留历史数据，故使用***h****istory*作为这个参数的名称），如果不使用参数`-h`，每一步刷新时会清空已显示的三行输出，之后再重新输出。

### 示例命令

```
./turing -t100000 -h < prog/plus.txt
```

## 输入

```
状态数
状态名称 转移个数
	输入字符 转移到的状态 写下字符 移动方向
	...
	输入字符 转移到的状态 写下字符 移动方向
...
状态名称 转移个数（-1代表final state）
初始串
初始状态
初始位置
```

### 示例输入

```
18
plus_switch_to_next 1
	1	plus_start_next 0 R
plus_start_next 2
	0	plus_move_to_copy 1 R
	1	plus_finish_back 1 L
plus_move_to_copy 2
	0	plus_move_to_copy 0 R
	1	copy_start 1 R
copy_start 2
	0	copy_start 0 R
	_	copy_back 0 S
copy_back 2
	0	copy_back 0 L
	1	plus_back_from_copy 1 L
plus_back_from_copy 2
	0	plus_back_from_copy 0 L
	1	plus_switch_to_next 1 S
plus_finish_back 2
	0	plus_finish_back 0 L
	1	plus_end 1 S
plus_end 1
	1	multiply_back_from_plus 1 L
plus_start 1
	1	plus_start_switch 1 R
plus_start_switch 2
	0	plus_move_to_copy 1 R
	1	plus_end 1 L
multiply_swtich_to_next 1
	1	multiply_start_next 0 R
multiply_start_next 2
	0	multiply_move_to_plus 1 R
	1	multiply_finish_back 1 L
multiply_move_to_plus 2
	0	multiply_move_to_plus 0 R
	1	plus_start 1 S
multiply_back_from_plus 2
	0	multiply_back_from_plus 0 L
	1	multiply_swtich_to_next 1 S
multiply_finish_back 2
	0	multiply_finish_back 0 L
	1	multiply_end 1 S
multiply_end -1
multiply_start 1
	1	multiply_start_switch 1 R
multiply_start_switch 2
	0	multiply_move_to_plus 1 R
	1	multiply_end 1 L
1000000010000001
multiply_start
0
```
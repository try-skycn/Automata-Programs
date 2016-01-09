状态数
状态名称 转移个数 输入字符 转移到的状态 写下字符 移动方向 ... 输入字符 转移到的状态 写下字符 移动方向
...
状态名称 转移个数（-1代表final state）
初始串
初始状态
初始位置

样例：
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

对于一个集合 {x1,x2...,xn} 其所有的子集个数为2^n个，该算法生成所有情况

方法：利用0，1序列来表示子集，1代表有元素，0代表无，则对于集合{x1,x2,x3}来说有8种情况:

(000) (001) (010) (011) (100) (101) (110) (111)

给出一个子集(000),则后续子集生成方法：**遍历数据序列到达最后一个0的位置，令其变为1，再将其右边所有元素置为0则生成下一个子集**。
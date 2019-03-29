//
// Created by gzbbxu on 2019/3/16.
//

#ifndef JNIDEMO_HASHNODE_H
#define JNIDEMO_HASHNODE_H
template <class T>
class hashnode{
public:
    T t;//代表数据
    int cn;//代表查找次数
    int key;//代表索引
};
#endif //JNIDEMO_HASHNODE_H

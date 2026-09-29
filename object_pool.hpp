#include <cstdio>
#include <cstdlib>
#include <iostream>

template <class T> class ObjectPool
{
public:
    T* New()
    {
        T* obj;
        if (free_linked_list)
        {
            obj = (T*)free_linked_list;
            free_linked_list = *((void**)free_linked_list); //前面保存的下一模块的地址
        }
        else
        {
            if (remain_size < sizeof(T))
            {
                sum_space = (char*)malloc(1024 * 1024);
                if (sum_space == nullptr)
                {

                    std::cout << "malloc error" << std::endl;
                    exit(1);
                }
                remain_size = 1024 * 1024;
            }

            obj = (T*)sum_space;
            size_t objSize = sizeof(T) < sizeof(void*) ? sizeof(void*) : sizeof(T);

            sum_space += objSize;
            remain_size -= objSize;
        }

        //定位new
        new (obj) T;
        return obj;
    }
    void Delete(T* obj)
    {
        //显示调用析构函数
        obj->~T();

        //头插用于删除模块
        *((void**)obj) = free_linked_list;
        free_linked_list = (void*)obj;

        
    }

private:
    char* sum_space = nullptr;        //未使用的大块内存
    void* free_linked_list = nullptr; //释放出来的空闲内存
    size_t remain_size = 0;           //大块内存剩余容量
};
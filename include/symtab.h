// symtab.h
#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdbool.h>

// ------------------------- 符号类型枚举 -------------------------
typedef enum {
    SYM_VARIABLE,       // 变量
    SYM_FUNCTION,       // 函数（有返回值）
    SYM_PROCEDURE,      // 过程（无返回值）
    SYM_PARAMETER,      // 函数/过程的参数
    SYM_TYPE,           // 类型定义（如数组、结构体）
    SYM_CONSTANT,       // 常量
    SYM_LABEL,          // 标签（goto 目标）
    SYM_ENUM_MEMBER     // 枚举成员
} SymbolType;

// ------------------------- 类型系统定义 -------------------------
typedef enum {
    TYPE_BASIC,         // 基础类型（integer/real/boolean/char）
    TYPE_ARRAY,         // 数组类型
    TYPE_POINTER,       // 指针类型
    TYPE_FUNCTION       // 函数类型
} TypeCategory;

// 基础类型枚举
typedef enum{
    INTEGER_TYPE,       // 整形
    REAL_TYPE,          // 浮点
    BOOLEAN_TYPE,       // 布尔
    CHAR_TYPE           // 字符
}BasicType;

// 数组范围定义
typedef struct {
    int lower_bound;                // 数组下界
    int upper_bound;                // 数组上界
    struct ArrayRange *next_range;  // 下一组维数指针
} ArrayRange;

// 数组类型详细信息
typedef struct {
    ArrayRange range;           // 数组范围（如 1..10）
    struct TypeInfo *element_type; // 元素类型
} ArrayInfo;

// 函数类型详细信息
typedef struct {
    struct TypeInfo *return_type;   // 返回值类型（过程为 NULL）
    struct ParamList *params;       // 参数列表
} FunctionInfo;

// 类型信息结构体
typedef struct TypeInfo {
    TypeCategory category;      // 类型类别
    union {
        BasicType basic;        // 基础类型名
        ArrayInfo array;        // 数组类型信息
        FunctionInfo function;  // 函数类型信息
    } details;
} TypeInfo;

// ------------------------- 参数列表结构 -------------------------
typedef struct ParamList {
    char *name;                 // 参数名
    struct TypeInfo *type;      // 参数类型
    struct ParamList *next;     // 下一个参数
} ParamList;

// ------------------------- 符号表条目 -------------------------
typedef struct SymbolEntry {
    char *name;                 // 符号名称
    SymbolType sym_type;        // 符号类型（变量/函数等）
    TypeInfo *data_type;        // 符号的类型信息
    int scope_level;            // 作用域层级
    struct SymbolEntry *next;   // 链表指针
} SymbolEntry;

// ------------------------- 符号表结构 -------------------------
typedef struct SymbolTable {
    SymbolEntry *entries;       // 符号条目链表
    struct SymbolTable *parent; // 父作用域
    int level;                  // 当前作用域层级
} SymbolTable;

// ------------------------- 全局变量定义 -------------------------
SymbolTable * Entry = NULL;

// ------------------------- 符号表操作接口 -------------------------
// 创建符号表
SymbolTable *symtab_create(int level, SymbolTable *parent);

// 插入符号条目
void symtab_insert(SymbolTable *table, SymbolEntry *entry);

// 查找符号条目（recursive 表示是否递归查找父作用域）
SymbolEntry *symtab_lookup(SymbolTable *table, const char *name, bool recursive);

// 销毁符号表（递归释放内存）
void symtab_destroy(SymbolTable *table);

// 创建符号条目
SymbolEntry *symtab_create_entry(const char *name, SymbolType sym_type, TypeInfo *data_type);

// ------------------------- 类型系统操作接口 -------------------------
// 创建基础类型
TypeInfo *type_create_basic(BasicType basic);

// 创建数组类型
TypeInfo *type_create_array(ArrayRange range, TypeInfo *element_type);

// 创建函数类型
TypeInfo *type_create_function(TypeInfo *return_type, ParamList *params);

#endif // SYMTAB_H
# MarkDown 语法学习
[toc]
## 基础语法

### 标题：

    # 一级标题
    ## 二级标题
    ### 三级标题
    #### 四级标题
    ##### 五级标题
    ###### 六级标题


### 强调 :

*斜体*

_斜体_

**粗体**
__粗体__

*邪**粗**体*

### 无序列表

- 测试
- 测试
- 测试

* 测试
* 测试
* 测试


### 有序列表

1. 一级列表
2. 2
    1. 二级列表
    2. 2

### 添加图片/超文本链接
![这是一张图片](https://ts2.cn.mm.bing.net/th?id=OIP-C.q4YiW9BCiugBoWQa8cti2gHaE7&w=306&h=204&c=8&rs=1&qlt=90&o=6&pid=3.1&rm=2)

[这是一张图片](https://ts2.cn.mm.bing.net/th?id=OIP-C.q4YiW9BCiugBoWQa8cti2gHaE7&w=306&h=204&c=8&rs=1&qlt=90&o=6&pid=3.1&rm=2)

图片形式为![描述](链接)
超文本链接为[描述](链接)

### 引用
>  引用这他妈是我说的

### 分割线
---
___ 

连续的三个或者更多连字符，下划线或者星号
*** 

### 代码
行内代码使用`括起来

我觉得你应该在这里使用
`<addr>` 才对。

代码块使用```括起来

```ruby
require 'redcarpet'
markdown = Redcarpet.new("Hello World!")
puts markdown.to_html
```

### 表格
First Header | Second Header
------------ | -------------
Content from cell 1 | Content from cell 2
Content in the first column | Content in the second column

### 任务列表
- [x] 计划一 已完成
- [ ] 计划二 未完成



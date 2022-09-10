
## JSON 交互格式说明

由于 `Word` 内容较多，调用时兼容很多写入场景，因此目前设计使用 `JSON` 格式来交互，基本覆盖大部分使用场景，而且支持各种自定义，完全满足日常使用，下面是各个字段的说明

### 全局配置

- savePath: 定义了生成的 `Word` 文档路径，确保该路径有写入权限，否则可能会失败
- openFile： 导入成功后是否打开该文档
- line_spacing： 行间距，默认给 1.5倍
- header： 页眉文本，不需要页眉直接给空即可
- footer： 页脚文本
- content：[] 这里是 `Word` 内容部分，采用数组存储，由于数组有有序的，因此严格按照你的内容顺序依次传入即可
- fontSize: 全局字体大小
- fontName: 全局字体名字，设置后后续每个正文、标题、表格等可以不用设置，全局统一
  
### 正文

下面是正文内容部分说明

- type: 标识是那种类型，0:标题,1: 普通文本,2:图片，3：表格，其它类型后续扩展自定义
- text： 如果是文本或者标题给定内容
- level： 级别，目前只有标题类型生效
- bold： 是否加粗
- italic： 是否倾斜
- strike: 是否删除线
- alignment： 对齐方式，主要有这么几种：left, right,center
- color: 对应文本的颜色
- height： 行高

### 插入表格

如果是表格，那么有这些扩展字段

- columns: 列数
- rows: 行数
- height： 行高，所有行设置一样的行高，也可以自定义每行的行高
- mergeCells： 要合并的单元格数组,比如合并 (0,0)和(0,1)单元格，那么内容如下
```
{"begin": [0,0], "end": [0,1]}
```
- tableCell: 单元格内容，依次填充每个单元格内容即可，每个单元格内容和普通文本类似，下面是一个示例

```
tableCell": [
                {"text": "我是第一个单元格,加粗，倾斜,红色", "style": "", "bold": true, "italic": true,"color": "#ff0000","alignment": "center"},
                {"text": "00和01合并了，02会覆盖01的值，加粗变红,左对齐", "style": "", "bold": true, "italic": false,"color": "#ff0000","alignment": "left"},
                {"text": "03", "style": "", "bold": false, "italic": false,"color": "#000000","alignment": "center"},
                {"text": "04", "style": "", "bold": false, "italic": false,"color": "#000000","alignment": "center"},
                {"text": "05", "style": "", "bold": false, "italic": false,"color": "#000000","alignment": "center"},
                {"text": "06", "style": "", "bold": false, "italic": false,"color": "#000000","alignment": "center"},
                {"text": "07", "style": "", "bold": false, "italic": false,"color": "#000000","alignment": "center"},
                {"text": "08", "style": "", "bold": false, "italic": false,"color": "#000000","alignment": "center"}
            ]
```

### 插入图片

图片字段和其它文本字段类似，额外添加图片路径属性即可

- picture: "./test.png"

注意图片路径支持相对路径和绝对路径，根据自己实际需要传递即可


## 总结

虽然示例程序可以满足大部分场景，但是如果某些特殊场景不满足时，可以自定义扩展这个`JSON` 结构，也欢迎大家完善这个程序


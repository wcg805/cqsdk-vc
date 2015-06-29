SDK作者: Coxxs，感谢 orzFly 在SDK开发过程中的帮助！

本SDK可能存在一些不成熟之处，欢迎加入开发群（见SDK说明文件）提出意见或建议，与我们一起完善该SDK！

----

CQPdemo.sln
//示例项目，可以直接在此基础上编写应用
//您可以编译为 com.coxxs.democ.dll，与 CQPdemo/com.coxxs.democ.json 一起放置在酷Q的app目录下测试

----

CQPdemo/com.coxxs.democ.json 
//样例应用的对应信息文件，包含应用的基础信息、事件列表等，请放置在酷Q的app目录下（用文本编辑器打开，复制到 next.cqp.cc/json 解析校验，无需使用的事件、菜单、权限请务必在此删除）

CQPdemo/cqp.h
//酷Q SDK 头文件，通常无需修改

CQPdemo/CQP.lib
//CQP.dll 的动态连接 .lib 文件，便于C、C++等调用 酷Q 的方法。
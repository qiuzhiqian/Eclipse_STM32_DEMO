# Eclipse搭建stm32+jlink开发环境全攻略  
## 初级篇  
**前言**：  
为什么需要这样的开发环境？

 1. 免费
 2. 跨平台
 3. 自由度高
 4. Eclipse代码提示功能强大，MDK弱爆了

注：本人原创，转载注明作者------by**秋之前**
### 一、工具：  

 1. jre或者jdk
[地址](http://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html)
 2. eclipse+CDT
[地址](https://www.eclipse.org/downloads/eclipse-packages/)
 3. GNU eclipse ARM插件
 [地址](https://sourceforge.net/projects/gnuarmeclipse/)
 4. GNU ARM Toolchain
[地址](https://launchpad.net/gcc-arm-embedded/)
 5. Jlink驱动
[地址](https://www.segger.com/jlink-software.html)
 6. st官方标准库
[地址](http://www.st.com/content/st_com/en/products/embedded-software/mcus-embedded-software/stm32-embedded-software/stm32-standard-peripheral-libraries/stsw-stm32054.html)
 7. st官方hal库
[地址](http://www.st.com/content/st_com/en/products/embedded-software/mcus-embedded-software/stm32-embedded-software/stm32cube-embedded-software/stm32cubef1.html)

安装提醒：

 1. 由于并不需要用到java，所以只需用安装jre即可，不用安装jdk
 2. 安装GNU ARM Toolchain时勾选将目录加入环境变量的选项，否则请自己添加bin目录到环境变量中
 3. 现状Jlink驱动和GNU ARM Toolchain，然后再装Eclipse，接着装CDT，在接着装GNU eclipse
    ARM插件。
 4. 插件安装的时候，取消掉需要联网的地址。否则安装比较慢。

### 二、新建工程：  
打开eclipse，选择工作目录，点击File->New->C++ project  
![](./pic/pic1.png)  
然后我们会发现下图的界面，在这个界面中有STM32等工程的现成选项，右侧还有该工程支持的编译链，如Cross Arm gcc，根据这个我们就可以判断前面的软件安装成功了。此时我们可以直接点击新建一个基于STM32模版的工程，也可以创建一个空的工程，然后自己配置工程结构，就像我们使用MDK一样。此处我们以创建空工程为例子。
点击Empty project，输入工程名和路径，Next。  
![](./pic/pic2.png)   
选择编译链，由于我们安装的是GNU ARM的工具链，所以选择对应的，然后指定工具链的路径。  
![](./pic/pic3.png)   
创建好了之后，我们就可以看到下图的效果了，可以看到，这个工程完完全全是一个空的。现在我们向这个工程中添加文件，  
![](./pic/pic4.png)   
![](./pic/pic5.png)   
就像我们之前在MDK环境下配置模版一样，先创建四个文件夹  
![](./pic/pic6.png)   
然后从官方库文件中拷贝对应文件到该工程对应文件夹下。
需要注意的是，官方库文件中有一些文件是与编译环境相关的，官方提供的环境有  
![](./pic/pic7.png)   
我们通过比较后发现，TrueSTUDIO和eclipse环境的工程文件格式是一样的，所以确定选用TrueSTDUIO工程的文件  
![](./pic/pic8.png)   
首先是启动文件
![](./pic/pic9.png)   
然后还有链接文件
![](./pic/pic10.png)   
这两个文件根据对应芯片容量决定。
文件拷贝完了后，将鼠标点到工程框中右键刷新，我们就可以看到工程结构更新了，如下图
![](./pic/pic11.png)   
正如在MDK环境下开发我们需要配置define项，include包含项和debug项一样，在eclipse也要做这些工作。

### 三、工程配置：
点击在工程浏览器中选中该工程，然后点击project->properties选择项，
![](./pic/pic12.png)   

就会弹出如下对话框，在这个对话框中主要在setting中配置，首先看看Tool setting，该选项有四块，即汇编(Assembler)选项，C编译器选型，C++编译器选项，链接选项，每一块中preprocessor用来设置预编译的，即设置define。includes用来设置路径包含的，所以启动文件等汇编文件要加到第一个选项块中，ld格式的链接文件要加到第四个块中
![](./pic/pic13.png)   
![](./pic/pic14.png)   
![](./pic/pic15.png)   


上面设置好了后，由于穿件工程时我们已经设置了编译器，所以这个地方应该是正确的，如下图
![](./pic/pic16.png)   

好了点击应用，OK。

### 四、开始编译：
![](./pic/pic17.png)   
然而立马就出现下面的问题，找不到make文件，通过查资料我们可以知道GNU Toolchain中是不自带make工具的，但是make工具其实都是一样的，所以我们能否使用Eclipse自带的make工具呢？
![](./pic/pic18.png)   
同样打开工程设置，点击Tool Chain Editor，选择Builder工具为CDT内部builder，
![](./pic/pic19.png)   


然后重新编译，可以看到编译进度了
![](./pic/pic20.png)   
然而又出错了，这个问题的大致意思是这两个指令的调用格式不正确，但是由于这两条指令是汇编指令，他的调用格式是由编译器决定的，我们怎么知道他的正确的调用格式呢？我们先通过搜索找到这条指令调用的地方。
![](./pic/pic21.png)   
![](./pic/pic22.png)   
![](./pic/pic23.png)   


既然这条汇编指令的格式是由编译器决定的，那么我们怎么知道这条指令正确的格式呢？还记得之前创建工程时有现成的工程模版吗？我们可以创建一个现成的工程模版，然后编译发现这个现成的模版编译是没有问题。然后对比两个工程中的这条指令格式，我们发现了一个惊人的差异，如下图：
![](./pic/pic24.png)   


好了，问题找到了，在这两条指令的=r中间加上一个&符号即可。两条指令中都要加。然后再编译
![](./pic/pic25.png)   
哈哈，编译通过，生成了可执行文件elf和hex，然而我们将编译信息拉到右边后可以发现，编译没有问题，但是在链接时出现了问题，即找不到Reset_Handler。怎么会找不到Reset_Handler呢，我们都知道Reset_Handler是在启动文件中定义了的，没有找到除非启动文件没有被编译。
![](./pic/pic26.png)   
于是我们来看看编译输出的文件夹，即debug文件夹，发现只有3个文件夹有输出，启动文件确实没有输出，为什么呢？初步怀疑是Eclipse没有识别启动文件。
![](./pic/pic27.png)   
![](./pic/pic28.png)   

我们打开窗体属性看看，即window->preferences:
![](./pic/pic29.png)   
然后找到File Type，我们可以看到，软件能够识别的汇编文件拓展为*.S是大写的S,而我们工程中的启动文件是小写的s，所以没有识别出来，我尝试将小写s格式添加进去发现添加失败，提示跟大写S重复，好吧，我们直接将启动文件改成大写S吧。
![](./pic/pic30.png)   
![](./pic/pic31.png)   



然后再编译，OK编译成功，也没有链接的错误。大功搞成
![](./pic/pic32.png)   
![](./pic/pic33.png)   

### 五、开始调试：
编译完成后，我们就要进行下载和调试了。首先进行调试的配置。
Run->Debug Configurations。
![](./pic/pic34.png)   
我们可以看到GDB SEGGER Jlink Debugging选项下面是空的，双击这个选项
![](./pic/pic35.png)   
然后就新建了一个选项卡，设置debug的名称，调试的工程和源文件
![](./pic/pic36.png)   
![](./pic/pic37.png)   

切换到Debugger选项卡，此处才是关键，我们都知道，调试实际就是我们的调试窗口与Jlink通讯，然后Jlink与开发板通讯，Jlink与开发板通讯是由Jlink GDBServerCL完成的，所以我们的调试窗口要与Jlink通讯，起始只需要与Jlink GDBServerCL通讯即可，那么是什么来代表这个调试窗口呢，那自然就是GNU工具链的GDB调试器了，所以我们整体的调试思路就清晰了，就是GNU GDB与Jlink GDBServerCL通讯，前者扮演客户端的角色，后者扮演服务器的角色。好了，再来看看这个配置窗口，服务器设置自然选择Jlink GDBServerCL，而客户端自然选择GNU工具链中的GDB了，然后设置芯片型号，链接模式，传输速度等。
![](./pic/pic38.png)   
为了保险，取消掉startup中的这连个选项
![](./pic/pic39.png)   
好了，点击Debug开始调试，我们就可以看到我们的软件进入了调试模式，并且停留在了main函数的第一个有效行上面。
![](./pic/pic40.png)   
点击红色方块结束调试，Jlink的GDB会自动关闭，然后点击右侧的C/C++选项卡即可回到工程的编辑视图了。
![](./pic/pic41.png)   
OK，初级篇教程到此结束，在初级篇中，我们可以开发一些并不涉及到C标准库函数的东西。


## 高级篇
### 一、问题概况
通过初级篇的学习，我们知道了一个Eclipse工程的配置以及调试，貌似使用也没什么问题，然而。当我们抛弃掉Eclipse自带的工程模版是，也抛弃的他的一些其他的功能，比如c库函数的支持。所以，如果我们按照这初级篇的内容建立一个工程，我们会发现，当我们使用了printf等C库的函数时，工程编译会报错。
这是没有加入printf是的编译情况，没有任何错误

而这个图就是加上了printf后编译的情况，当然stdio.h还是要加上去的，

可以看到，只要加上了printf后编译就会出问题。
### 二、问题分析
为了解决这个问题，我们先探索一下这个问题产生的原因。众所周知，printf调用的是标准的C库函数，那么我们搭建的GNU环境是否有C库呢？通过查阅GNU ARM ToolChain官网，我们可以知道，gun工具链支持C库，默认的是newlib库。
那么，什么是newlib？摘录一段百度百科的介绍，当然这段介绍是对newlib引文手册的一段翻译，英文可以的同学可以看看英文的。

既然我们搭建的环境中存在了C支持库，那么为什么还会编译错误呢？我们接着看。

什么意思？就是说我们的newlib是存在了，但是newlib的20个桩函数还没有实现，即只是存在newlib，但是还没有移植。为什么gnu不帮我们移植好呢？正如上面介绍的那样，这20个桩函数是与运行的平台息息相关的，也就是说，如果我用的是51，可能这些函数是一种实现方式，如果我用的STM32，可能是另外一种形式(举个例子而已，并不准确)。所以我们现在的工作就是要把newlib没有完成的工作完成就可以了，即实现20个桩函数。
难道真的要我们自己写吗？不会写啊！不用担心，如果真的要我们自己写，那么这个教程的实用性就太低了。
通过上面的教程我们可以知道，我们的文件都是通过st官方中的TrueSTUDIO编译器的文件提取过来的，但是遗憾的是标准库中对TrueSTUDIO没有一个完整的范例，所以有一些文件其实是缺失的。而且标准库也很久没有更新了，但是st官方还有一个hal库，这个库是标准库的升级版，我们可以从hal库中得到我们想要的东西。
下载官方stm32f1的hal库，全文件夹下搜索一下syscalls，我们就可以搜到我们想要的syscalls.c文件，比如在STM32Cube_FW_F1_V1.4.0\Projects\STM32F103RB-Nucleo\Examples\UART\UART_Printf\TrueSTUDIO文件夹下就有一个syscalls.c，打开这个文件

我们可以发现这个文件将我们需要的newlib桩函数全部实现了，我们只要将这个文件添加到工程中就大功告成了。
[注]：通过自带模版的newlib文件桩函数这种方法在后面可能会产生一些bug，所以这个方法被我抛弃了。
### 三、问题解决
我们在eclipse工程目录下新建一个叫做newlib的文件夹，然后将hal库中的syscalls.c这个文件复制进去。

然后刷新工程，

我们编译一下编译，你就会惊奇的发现没有错误了

我们此时只是添加了对printf的支持，但是还没有对printf进行重定向到串口，在newlib中，printf输出时会调用syscalls中的_write函数，scanf输入会调用syscalls中的_read函数，

而_read会调用__io_getchar()获取一个字符，_write会通过__io_putchar()输出一个字符，而且这两个函数都是弱类型，可以重写的。所以我们的重定向函数可以这么写(比如我重定向到串口5)

好了重新编译，然后进行调试

然后就可以看到输出结果了。

但是有的同学发下添加了syscalls后进行了重定向后我们仍然无法通过printf输出到串口，这是因为printf输出依赖于\n，也就是说只有碰到\n后才会将printf缓冲区中的内容输出，所以printf(“abc”)这样的语句是不会立即输出的，要想立即输出需要写成这样printf(“abc\n”),要换行就写成printf(“abc\r\n”)，或者分两句写printf(“abc”)；printf(“\r\n”);


## 进阶篇(一)
本篇开始讲解一些比较实用的东西，在前面的两章中，我们讲解了eclipse开发stm32的大部分问题，然而。在实际使用过程中，我们仍然会遇到一些不太理想的地方，比如，eclipse不能一键下载，只能通过调试变相的下载，很不方便。同时eclipse编译出来的文件要比MDK编译的文件大很多。本篇就是为了解决这两个问题的：程序优化和一键下载。
先说说文件过大的问题，这个问题是由于我们默认的工程优化比较小。
### 1、优化等级
-O0
-O1
-O2
-O3
-Os

自己酌情选择。我通常选择O0


这两个选项会滤除掉没有使用过的函数和数据


使用newlib-nano选项会进一步去除大量newlib中不常用的库函数，从而大大减小文件体积。
注意以上三点后，编译出来的文件基本上就跟MDK编译的文件大小还差不多了。

另外说一点就是eclipse支持编译生成不同格式的文件，包括最原始的elf，还有bin、hex等其他格式。设置的地方在图中所示的地方



### 2、一键下载
接着，我们需要有一个一键下载的功能。
该部分参考了http://bbs.elecfans.com/jishu_564620_1_1.html的下载部分内容。
首先，我们需要知道对于jlink，下载使用JLink.exe，调试使用JLinkGDBServerCL。为了更好的使用eclipse下载，我们先来熟悉一下直接使用jlink命令下载的流程。
1、将jlink安装目录添加到环境变量
2、点开cmd，将目录切换到bin文件目录下

3、运行JLink.exe，然后会提示让我输入connect，接着提示让我输入芯片型号、TIF模式、速度等选项，然后才算成功连接。

那么我们能不能只通过一步就将这些选项设置好呢？可以
看看JLink的命令手册

就是这三个选项了。
所以我们可以这样重新些JLink命令：JLink.exe -autoconnect 1 -device stm32f103rc -if swd -speed 4000

接着我们就进入了JLink命令模式，再来看一看JLink有哪些命令可以使用

常用的差不多就这几个了
先运行h，让jlink暂停

然后运行loadfile下载bin文件到0x08000000

然后用r命令重启开发板，在用g命令运行程序，最后用exit或者q命令推出jlink模式

肯定又有同学说好麻烦，没有更简单的方法吗？有，我们只需要将上面的这些命令做成一个脚本，然后将这个脚本作为一个参数传递给JLink启动命令选项即可自动执行了。
细心的同学可能已经注意到了前面图中的一个参数

这两个参数是一个意思，随便用一个即可，比如-commandfile。
首先我们写一个自动命令的脚本，名字就叫做download.jlink
然后运行这样一条指令即可实现一步下载了
JLink.exe -autoconnect 1 -device stm32f103rc -if swd -speed 4000 -commandfile download.jlink

从图中可以看出指令的运行情况，jlink成功连接上了stm32，并且载入了命令脚本，执行命令脚本，下载bin文件，重新启动，运行。
那么，现在我们要解决的问题是怎么让eclipse运行这样一条指令。
我们可以注意到在eclipse上有这样一个按钮：external tool

打开设置
仿照着这个图中设置

其中脚本路径的地方${workspace_loc:/UCOS_Demo}代表了我的工程目录，换成自己对应的即可。同时，路径对应自己的实际路径。比如我是在工程目录下面新建了一个jlink文件夹，脚本放在了这个文件夹下了。
另外loadfile的文件路径需要填写自己实际路径

然后把图中所示的地方选中，确定。然后点击那个拓展按钮就可以实现下载了。



## 进阶篇(二)
我们设计程序往往会遇到这样的一个需求，那就是我们的程序起始位置需要重新定位，并不是默认的0x08000000，这种情况往往出现在有使用bootloader的情况中，0x08000000处往往存放我们的bootloader程序，然后0x08000000+N出存放我们的应用程序(APP)。那在MDK下这种情况很好解决，无非就是修改几个地址和大小变量。在eclipse中也同样简单。
比如现在，我使用的芯片为stm32f103rc，flash=256K，ram=48K，我需要把我的程序下载到0x08004000处，并且能够通过已经编译好的bootloader启动这个程序，根据前面的相关章节，我们可以知道：
1\首先我们编译的时候，需要将输出文件的起始地址定位为0x08004000
2\然后我们在下载的时候，我要将二进制文件烧写到flash中的0x08004000处
3\调试程序的时候我们也能够正确的将调试器定位到0x08004000处来正确的启动调试
我们一步一步来解决上面的三个地方。

### 1、修改编译地址:
这个地址应该叫做链接地址，在链接文件中

如图所示，我将FLASH的ORIGIN修改为0x08004000，因为我的bin文件需要链接到这个地址，那么flash的剩余空间也要跟着调整,0x4000=16K,原本flash有256K，所以剩余240K。由于我的ram不需要修改，所以_estack和ram段的值都没有变。

### 2、修改下载地址:
前面我们已经讲解了使用jlink脚本进行一键下载，下载由于我们的下载地址改变了，那么我们只需要修改脚本中的loadfile的目的地址即可


### 3、修改调试地址
如果细心的同学可能已经发现了，在eclipse的jlink调试选项中，已经自带有修改调试偏移地址的选项，如下图所示

只需要修改下面的偏移地址即可，上面的应该是对应ram的吧。
测试一下

可以看到点击调试后首先进行程序的下载，可以看到程序被下载到0x08004000，这个地址正是我们期望的地址，说明没问题。然后启动gdb后停止在了main函数的开始位置，OK一切正常。


# 第二周   
## 操作系统运行环境与运行机制   

### 操作系统主要的工作    
> - 程序的执行    
> > 启动程序，执行程序以及程序结束的工作    
> - 完成与体系结构相关的工作    
> - 完成应用程序所需的共性任务  
> > 提供各种基本服务    
> - 性能，安全，健壮等问题   

### 操作系统运行环境   
> - CPU状态   
> - 中断/异常机制   

#### 处理机状态(模式)     
> 处理器是由**控制器**，**运算器**，一系列的**寄存器**和**高速缓存**组成    

* 两类寄存器   
> - 用户可见寄存器     
> > 高级语言编译器通过优化算法分配并使用，以减少访问内存的次数   
  
> - 控制和状态寄存器    
> > 用于控制处理器的操作，通常由操作系统代码使用   
> > 在某种特权级别下可以访问，修改  

> * 常见的控制和状态寄存器   
> > - 程序计数器(PC):记录了下一条指令的地址   
> > - 指令寄存器(IR):记录最近取出的指令   
> > - 程序状态字(PSW)：记录处理器的运行状态，如条件码，模式，控制位信息等   

#### 操作系统的需求--保护   
> 从操作系统的特征考虑(并发，共享)，因此对硬件提出了要求(实现保护和控制)   

> * 需要硬件提供基本运行机制  
> > - 处理器具有特权级别，能在不同的特权级别下运行不同的指令集合    
> > - 硬件机制可以将OS与用户程序隔离   

#### 处理器的状态(模式)   
> 现代处理器通常将CPU的状态设置为2种，3种或4种     
> 在程序状态字寄存器PSW中专门设置一位，根据运行程序对**资源和指令的使用权限**而设置不同的CPU状态,例如X86构架中的EFLAGS寄存器
有两位(IOPL)标志CPU的状态   

#### 特权指令和非特权指令   
* 操作系统需要两种CPU状态  
> - 内核态：运行操作系统代码   
> - 用户态 ：运行用户程序    

* 特权指令   
> 只能由操作系统来使用，用户程序不能使用   
> 比如启动IO，内存清零，修改程序状态字，设置时钟，允许/禁止中断，停机
* 非特权指令  
> 用户程序可以使用的指令    
> 比如控制转移，算数运送，取数指令，访管指令    

##### 实例：X86系列处理器  
> X86支持4个处理器特权级别，分别为R0,R1,R2,R3,称为特权环   
> - 从R0到R3，特权能力由高到低    
> - R0相当于内核态，R3相当于用户态，R1和R2介于两者之间    
> - 不同级别运行不同的指令集合，R0运行所有指令，R3只是运行指令集中最小的子集      
> 目前大部分的X86处理器都只使用R0和R3特权级别   

#### CPU状态的转换    
* 用户态->内核态  
> 只有唯一的途径：中断/异常/陷入    

* 内核态->用户态  
> 设置程序状态字寄存器    

* 一条特殊的指令
> 陷入指令，又称访管指令，是提供给用户程序的接口，用于调用操作系统的服务     
> 例如，int, trap,syscall,sysenter/sysexit    

### 中断和异常机制   
> 操作系统是由"中断驱动"或"事件驱动"的   

* 主要作用   
> - 及时处理设备发来的中断请求 (中断) 
> - 可使OS捕获用户程序提出的服务请求(系统调用)    
> - 防止用户程序执行过程中的破坏性活动 (异常)   

#### 中断与异常的概念   
> CPU对系统发生的某个事件作出的一种反应,可以说事件的发生改变了处理器的控制流      

* 特点   
> - 是随机发生的   
> - 是自动处理的   
> - 是可恢复的   

##### 为什么引入中断和异常    
> 中断的引入是为了支持CPU和设备之间的并行性，可以使CPU和设备独立工作    
> 异常的引用是为了表示执行指令时本身出现的问题，比如除零，算数溢出     

##### 事件分为   
* 中断(外中断)   
> 外部事件，正在运行的程序所部期望的  
> - I/O中断  
> - 时钟中断   
> - 硬件故障    

* 异常(内中断)    
> 由正在执行的指令引发的   
> - 系统调用   
> - 页故障/页错误   
> - 保护性异常   
> - 断点指令   
> - 其他程序性异常(如算术溢出)     

#### 中断与异常工作原理    
* 中断与异常机制是现代计算机系统的核心机制之一    
> 软件与硬件相互配合而使计算机系统得到充分发挥能力  

* 硬件做什么呢   ---中断/异常响应       
> 捕获中断源发出的中断/异常请求，以一定方式响应，将处理器控制权交给特定的处理程序      

* 软件做什么呢   ---中断/异常处理程序    
> 识别中断/异常类型并完成相应的处理    

##### 中断响应    
> 发现中断，接收中断的过程，由中断硬件部件完成    
> 处理器控制部件中有**中断寄存器**，CPU在执行每条指令的最后时刻扫描中断寄存器，查看是否有中断信号，若有中断，中断硬件将
该中断触发器内容按规定编码送到PSW的响应位，称为**中断码**，通过查**中断向量表**引出中断处理程序，若无中断或禁止中断，则执行下一条指令     

##### 中断向量表   
* 中断向量   
> 一个内存单元，存放中断处理程序的入口地址和程序执行所需要的处理机状态字 ，若干中断向量构成中断向量表.如Linux系统中，0-19号中断向量用于不可屏蔽中断和异常     

##### 中断响应过程    
* 设备发送中断信号     
* 硬件保存现场 主要是PSW和PC    
* 根据中断码查表    
* 把中断处理程序入口地址推送到相应的寄存器   
* 执行中断处理程序   

##### 中断处理程序   
* 设计操作系统时，为每一类中断/异常时间编好相应的处理程序，并设置好相应的中断向量表(系统启动时完成)    
* 系统运行时若响应中断，中断硬件部件将CPU控制权交给中断处理程序    
> - 保存相关寄存器的信息 (PC和PSW和其他信息)       
> - 分析中断/异常的具体原因(查中断向量表)    
> - 执行对应的处理程序   
> - 回复现场，返回被打断的程序      

##### X86中断/异常机制   
* 中断   
> 由硬件信号引发的，分为可屏蔽中断和不可屏蔽中断    

* 异常    
> 由指令执行引发的，比如除零异常，X86处理器大约发布了20多种异常    
> 对于某些异常，CPU会在执行异常处理程序之前会产生硬件出错码，并将其压入内核态堆栈    

* 系统调用   
> 异常的特殊的情况，用户态到内核态的唯一一种方式    

* 中断控制器  
> 负责将硬件的中断信号转化为中断向量，并引发CPU中断    

* 实模式   :中断向量表
> - 入口地址=段地址左移4位 + 偏移地址   
> - 不支持CPU运行状态的切换   
> - 中断处理与一般的过程调用类似   

* 保护模式  :中断描述符表   
> 采用**门描述符**数据结构表示中断向量     

##### 四种类型门描述符   
* 任务门   
* 中断门    
> - 给出段选择符，中断/异常处理程序的段内偏移量    
> - 通过中断门后，系统会自动禁止中断   
     
* 陷阱门     
> 与中断门类似，但是通过陷阱门后系统不会自动禁止中断   
  
* 调用门   

##### 例子    
> 通过IDTR可以找到IDT(中断描述符表)，中断描述符有64位，内含门类型，特权级，段选择符,偏移    
> 段选择符包括**索引**，**GDT/LDT**，**特权级**    
> 通过GDTR可以找到GDT(全局描述符表)，用段选择符中的索引查此表    
> 通过GDT可以找出段描述符，段描述符中包含基地址          

##### 中断/异常的硬件处理过程    
* 确定与中断/异常相关的中断向量i    
* 通过IDTR寄存器找到IDT表，获得中断描述符(表中的第i项)    
* 从GDTR寄存器中找到GDT表，利用中断描述符中的段选择符，从GDT表中获得相应的段描述符，从该段描述符中获得中断/异常处理程序的
段基址     
* 特权级检查    
* 检查是否发生了特权级的变化，如果是，则进行堆栈切换(必须使用新的与特权级相关的栈)     
* 硬件压栈，保护上下文环境，若果硬件产生了异常出错码，也将它保存在栈中    
* 如果是中断，清IF位 (禁止中断)       
* 通过中断描述符中的偏移与段描述符中的基地址，找到中断处理程序的入口地址，执行第一条指令    
   
### 系统调用机制     
#### 系统调用概念   
<<<<<<< HEAD
> 用户在编程时可以调用的操作系统功能     
=======
> 用户在编程时可以调用的操作系统功能,全称为操作系统功能调用     
>>>>>>> 操作系统运行环境与运行机制

#### 系统调用的作用   
* 系统调用是操作系统提供给编程人员的唯一接口   
* 使CPU状态由用户态转化为内核态   

#### 典型的系统调用   
> 每个操作系统的都提供几百种系统调用，包括进程控制，进程通信，文件使用，目录操作，设备管理，信息管理    

#### 系统调用，库函数，API，内核函数   
> 应用程序可以直接调用系统调用或者C函数库/API接口，C函数库的部分是对系统调用的封装，内核是系统调用的处理程序    

#### 系统调用机制的设计   
* 中断/异常机制    
> 支持系统调用机制的实现   
  
* 选择一条特殊指令(访管指令，陷入指令)    
> 引发异常，完成用户态到内核态的切换   

* 系统调用号和参数  
> 每个系统调用都要给定一个编号(功能号)    

* 系统调用表   
> 存放系统调用服务例程的入口地址    

##### 怎么实现用户程序中的参数传递给内核呢   
##### 常用的有3中实现方法   
* 由陷入指令自带参数   
> 陷入指令的长度有限，且还要携带系统调用功能号，所以携带的参数有限    

* 通过通用寄存器传递参数   
> 这些寄存器是操作系统和用户程序都能访问的，但寄存器的个数会限制参数传递的个数    

* 在内存中开辟专用堆栈区来传递参数   

##### 系统调用的执行过程   
> 当CPU执行到一条特殊的陷入指令时   
    
* 中断/异常机制   
> 硬件保护现场，通过查中断向量表将CPU的控制权转交给系统调用总入口程序    

* 系统调用总入口程序   
> 保存现场，将参数保存在内核栈里，通过查**系统调用表**把控制权转交给相应的系统调用处理例程或内核函数    

* 执行系统调用例程   
* 恢复现场，返回用户程序    

##### 例子：Linux系统的系统调用的实现   
* 陷入指令选择128号  int $0x80    
* 门描述符  
> - 系统初始化时，对IDT中的128号门初始化    
<<<<<<< HEAD
> - 门描述符的2，3两个字节：内核代码段选择符，0，1，6，7四个字节：偏移量 ，入口地址指向(system_call())     
> - 门类型：陷阱门 (允许其他中断)   
> - 特权级：3  与用户级别相同，允许用户进程使用该门描述符   
      
=======
> - 门描述符的2，3两个字节：内核代码段选择符，0，1，6，7四个字节：偏移量 ，入口地址指向(system_call()) ,在`sched_init`中`set_system_gate(0x80, &system_call)`中实现
> - 门类型：15 陷阱门 (允许其他中断)   
> - 特权级：3  与用户级别相同，允许用户进程使用该门描述符   
* 系统执行`INT $0x80`指令 
> - 由于特权级别的改变，要切换栈， 用户栈->内核栈，CPU从任务状态段TSS中装入新的栈指针(SS:ESP),指向内核栈    
> - 用户栈信息(SS:ESP),EFLAGS,用户态CS，EIP寄存器的内容压栈(返回后使用)，由硬件完成       
> - 将EFLAGS压栈后，复位TF位，IF位保持不变   
> - 用128在IDT中找到该门描述符，从中找出段选择符转入段寄存器CS    
> - 代码段描述符中的基地址+陷阱门描述符中的偏移，可以定位`system_call()`的入口地址   

##### 中断发生后OS底层工作步骤 
- 硬件压栈：程序计数器等   
- 硬件从中断向量装入新的程序计数器等  
- 汇编语言过程保存寄存器的值   
- 汇编语言过程设置新的堆栈   
- C语言中断服务程序运行 (如读写操作)  
- 进程调度程序决定下一个讲运行的进程   
- C语言过程返回至汇编代码  
- 汇编语言过程开始运行新的当前进程  

# 本讲重点  
1. 理解计算机系统的保护机制   
- 掌握处理器状态  
- 掌握特权指令与非特权指令   
2. 掌握中断/异常机制  
- 掌握中断/异常的基本概念  
- 理解中断/异常机制的工作原理   
3. 掌握系统调用机制  
- 掌握系统调用设计原理 
- 掌握系统调用执行过程  

## 重点概念  
CPU状态  内核态/用户态  特权指令/非特权指令  中断  异常  中断响应  中断向量   中断处理程序   系统调用  陷入指令  系统调用号  系统调用表       
>>>>>>> 操作系统运行环境与运行机制



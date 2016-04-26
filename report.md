#eisenberg report
由于引用了pthread，使用g++编译时，要增加参数-pthead
测试程序创建了四个线程，每个线程会索取三次资源而后结束
一种可能的输出：
order:3 2 4 1
Process 3 starts
Process 3 fetches the resource
Process 3 is running
Process 3 releases the resource
Process 3 assignes 3 to the variable turn
Process 4 starts
Process 1 starts
Process 2 starts

Process 3 fetches the resource
Process 3 is running
Process 3 releases the resource
Process 3 assignes 4 to the variable turn

Process 4 fetches the resource
Process 4 is running
Process 4 releases the resource
Process 4 assignes 1 to the variable turn

Process 1 fetches the resource
Process 1 is running
Process 1 releases the resource
Process 1 assignes 2 to the variable turn

Process 2 fetches the resource
Process 2 is running
Process 2 releases the resource
Process 2 assignes 3 to the variable turn

Process 3 fetches the resource
Process 3 is running
Process 3 releases the resource
Process 3 assignes 4 to the variable turn

Process 4 fetches the resource
Process 4 is running
Process 4 releases the resource
Process 4 assignes 1 to the variable turn

Process 1 fetches the resource
Process 1 is running
Process 1 releases the resource
Process 1 assignes 2 to the variable turn

Process 2 fetches the resource
Process 2 is running
Process 2 releases the resource
Process 2 assignes 4 to the variable turn

Process 4 fetches the resource
Process 4 is running
Process 4 releases the resource
Process 4 assignes 1 to the variable turn

Process 1 fetches the resource
Process 1 is running
Process 1 releases the resource
Process 1 assignes 2 to the variable turn

Process 2 fetches the resource
Process 2 is running
Process 2 releases the resource
Process 2 assignes 2 to the variable turn

分析：
线程3最先执行，第一轮由于只有线程3，资源会再次分配给自己，同时线程4、2、1均启动，然后顺序执行两轮，第三轮由于线程3已经结束，故线程2结束后使用权会交给线程4。
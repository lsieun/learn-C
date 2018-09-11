# Introduction to Signals Using Alarm() in Linux C

URL: https://aljensencprogramming.wordpress.com/2014/05/09/introduction-to-signals-using-alarm-in-linux-c/

A signal is the software equivalent of a hardware interrupt. Signals provide a means for handing asynchronous events, with asynchronous here meaning “unpredictable”.

There are several dozen different signals, each with a different meaning. Every one of these signals has a name, beginning with the three letters `SIG`. Each signal is specified by its `number`, but we mostly use signals by their names. To utilize signals, we must include the header file `signal.h`.

> 这段了解2点：  
> （1）signal的name和number  
> （2）使用signal，要包含signal.h头文件。

The most commonly used signals are `SIGHUP`, `SIGQUIT`, `SIGKILL`, and `SIGTERM`. Each of these signals has a numeric value. `SIGKILL`, 9, is perhaps the most notorious, as it issues an unblockable kill signal.

> 这里介绍了几个常见的signal。

```c
#include<stdio.h>
#include<signal.h>

int main(void){
    printf("SIGHUP = %d\n", SIGHUP);
    printf("SIGQUIT = %d\n", SIGQUIT);
    printf("SIGKILL = %d\n", SIGKILL);
    printf("SIGTERM = %d\n", SIGTERM);

    return 0;
}
```

Output:

```txt
SIGHUP = 1
SIGQUIT = 3
SIGKILL = 9
SIGTERM = 15
```

Every **signal** has a default action associated with it; this is known as the **signal’s disposition**.

> 总的来讲，每一个signal都有默认的signal handler。


The `alarm()` function sets a timer that generates the `SIGALARM` signal. If we ignore or don’t catch this signal, the process is terminated.

> 单单拿出alarm()方法来讲，它的默认signal handler的行为是结束进程。

```c
#include<stdio.h>
#include<unistd.h>
#include<signal.h>

static void alarmHandler(int signo);

int main(void){
    alarm(5);

    signal(SIGALRM, alarmHandler);

    for(int i = 1; i < 10; i++){
        printf("%d\n", i);
        sleep(1);
    }

    return 0;
}

static void alarmHandler(int signo){
    printf("Alarm signal sent!\n");
}
```

Output:

```txt
1
2
3
4
5
Alarm signal sent!
6
7
8
9
```

Note that there is **only one** alarm clock per process. While the default action for `SIGLARM` is to **terminate the process**, usually we will want to catch this signal.

> 每一个进程只能有一个alarm clock。

The `wait()` function will cause a process to wait until a child process terminates.

> wait()的作用是等待子进程结束。  
> 下面的代码中展示了：父进程和子进程可以拥有各自的alarm()方法。

```c
#include<stdio.h>
#include<stdlib.h> // for exit() function
#include<unistd.h>
#include<signal.h>
#include<wait.h>
#include<sys/types.h>

static void catchAlarm(int signo);

int main(void){

    int status;
    pid_t pid;

    signal(SIGALRM, catchAlarm);
    pid = fork();

    if(pid < 0){
        printf("Problem forking process.\n");
        printf("Exiting now...\n");
        exit(EXIT_FAILURE);
    }

    if(pid == 0){
        alarm(5);
        for(int i=0; i<7; i++){
            printf("In child process... %d\n", i);
            sleep(1);
        }
    }
    else{
        wait(&status);
        alarm(7);
        for (int i=0; i<15; i++){
            printf("In parent process...%d\n", i);
            sleep(1);
        }
    }

}

static void catchAlarm(int signo){
    printf("Caught an SIGALRM signal.\n");
    printf("Signal value = %d\n", signo);

    printf("Exiting from process...\n");

    //in stdlib.h header file
    exit(EXIT_SUCCESS);
}
```

Output:

```txt
In child process... 0
In child process... 1
In child process... 2
In child process... 3
In child process... 4
Caught an SIGALRM signal.
Signal value = 14
Exiting from process...
In parent process...0
In parent process...1
In parent process...2
In parent process...3
In parent process...4
In parent process...5
In parent process...6
Caught an SIGALRM signal.
Signal value = 14
Exiting from process...
```

Note that the `alarm()` function will return a value if another alarm has been previously set.

> 我测试了一下，第二个alarm的返回值，就是第一个alarm的传入参数值。

The `pause()` function suspends the process until a signal is caught.

> 这里讲pause()的作用，应该是对所有的signal有效，不只是包括SIGALRM。

```c
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

static void catchSignal(int signo);

int main(void){
    alarm(7);

    signal(SIGALRM, catchSignal);

    //remember, a process can have only one alarm
    if(alarm(5) > 0){
        printf("An alarm has already been set.\n");
    }

    pause();

    printf("We should not see this text.\n");

    return 1;
}

static void catchSignal(int signo){
    printf("Caught the %d signal\n", signo);
    printf("Exiting now...\n");

    exit(EXIT_SUCCESS);
}
```

Output:

```txt
An alarm has already been set.
Caught the 14 signal
Exiting now...
```

Remember, a process can have **only one** alarm.
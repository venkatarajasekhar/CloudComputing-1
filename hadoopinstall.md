```sh
    yum -y update
    yum install wget
    systemctl stop firewalld
```

[ yum을 이용하여 Chrome 브라우저 설치 ]

```sh

# vi /etc/yum.repos.d/google.repo 

다음 내용 추가

[google64]
name=google-chrome - 64-bit
baseurl=http://dl.google.com/linux/rpm/stable/x86_64
enabled=1
gpgcheck=1
gpgkey=https://dl-ssl.google.com/linux/linux_signing_key.pub

```

```sh
yum으로 Google Chrome 안정판 설치
# yum install google-chrome-stable

다음과 같은 에러가 발생하여 설치가 중단된다.

Error: Package: google-chrome-stable-30.0.1599.114-1.x86_64 (google64)
       Requires: libstdc++.so.6(GLIBCXX_3.4.15)(64bit)
       
Richard Lloyd가 만든 설치 스크립트를 이용하여 다시 설치

# wget http://chrome.richardlloyd.org.uk/install_chrome.sh
# chmod u+x install_chrome.sh
# ./install_chrome.sh

```


[Hadoop 설치하기]]

```sh

    [기존 java 삭제하기]

    yum -y remove "java-*"
```

    1. jdk 다운로드
```
arch명령어를 통해 비트수 확인 후 설치
```


```sh
    cd ~/Downloads

    wget —no-check-certificate --no-cookies --header "Cookie: oraclelicense=accept-securebackup-cookie" http://download.oracle.com/otn-pub/java/jdk/8u5-b13/jdk-8u5-linux-x64.tar.gz

    (32비트인경우)
    wget --no-cookies --no-check-certificate --header "Cookie: gpw_e24=http%3A%2F%2Fwww.oracle.com%2F; oraclelicense=accept-securebackup-cookie" "http://download.oracle.com/otn-pub/java/jdk/8u60-b27/jdk-8u60-linux-i586.tar.gz"
    

    cd ~/Downloads/
    tar –zxvf jdk-8u5-linux-x64.tar.gz
    mkdir /usr/java
    mv jdk1.8.0_05 /usr/java/jdk1.8

    vi /etc/profile

    밑에 추가

    export JAVA_HOME=/usr/java/jdk1.8
    export PATH=$JAVA_HOME/bin:$PATH
    export CLASSPATH=$CLASSPATH:$JAVA_HOME/jre/lib/ext:$JAVA_HOME/lib/tools.jar

    source /etc/profile
```

    2. 계정 추가

```sh
    useradd hadoop
    su - hadoop
    ssh-keygen -t dsa -P '' -f ~/.ssh/id_dsa
    cat ~/.ssh/id_dsa.pub >> ~/.ssh/authorized_keys
    chmod 0600 ~/.ssh/authorized_keys
```

    3. 로컬호스트 들어갔다 나오기

```sh
    ssh localhost
    exit
    (ctrl + d)
```

    4. 하둡다운로드
    
```sh
    wget http://apache.tt.co.kr/hadoop/common/hadoop-2.7.1/hadoop-2.7.1.tar.gz
    tar -zxvf hadoop-2.7.1.tar.gz
```

    5. 컨피규어링

```sh
    $vi $HOME/.bashrc
    export JAVA_HOME=/usr/java/jdk1.8
    export HADOOP_CLASSPATH=${JAVA_HOME}/lib/tools.jar
    export HADOOP_HOME=/home/hadoop/hadoop-2.7.1
    export HADOOP_INSTALL=$HADOOP_HOME
    export HADOOP_MAPRED_HOME=$HADOOP_HOME
    export HADOOP_COMMON_HOME=$HADOOP_HOME
    export HADOOP_HDFS_HOME=$HADOOP_HOME
    export HADOOP_YARN_HOME=$HADOOP_HOME
    export HADOOP_COMMON_LIB_NATIVE_DIR=$HADOOP_HOME/lib/native
    export PATH=$PATH:$HADOOP_HOME/sbin:$HADOOP_HOME/bin
    export JAVA_LIBRARY_PATH=$HADOOP_HOME/lib/native:$JAVA_LIBRARY_PATH

    $source $HOME/.bashrc
```

    6. 속성값 추가하기 : <configuration> </configuration> 사이에

```sh
    vi $HADOOP_HOME/etc/hadoop/core-site.xml

    <property>
        <name>fs.default.name</name>
        <value>hdfs://localhost:9000</value>
    </property>
```

-------------------------------------------------

```sh
    vi $HADOOP_HOME/etc/hadoop/hdfs-site.xml

    <property>
        <name>dfs.replication</name>
        <value>1</value>
    </property>
 
    <property>
        <name>dfs.name.dir</name>
        <value>file:///home/hadoop/hadoopdata/hdfs/namenode</value>
    </property>
 
    <property>
        <name>dfs.data.dir</name>
        <value>file:///home/hadoop/hadoopdata/hdfs/datanode</value>
    </property>
```

-------------------------------------------------

```sh

    cp $HADOOP_HOME/etc/hadoop/mapred-site.xml.template $HADOOP_HOME/etc/hadoop/mapred-site.xml
    
```
-------------------------------------------------

```sh

    vi  $HADOOP_HOME/etc/hadoop/mapred-site.xml

    <property>
        <name>mapreduce.framework.name</name>
        <value>yarn</value>
    </property>
```

-------------------------------------------------

```sh
    vi $HADOOP_HOME/etc/hadoop/yarn-site.xml

    <property>
        <name>yarn.nodemanager.aux-services</name>
        <value>mapreduce_shuffle</value>
    </property>
```

-------------------------------------------------

```sh
    set JAVA_HOME
```

-------------------------------------------------

```sh
    vi $HADOOP_HOME/etc/hadoop/hadoop-env.sh 
    export JAVA_HOME=/usr/java/jdk1.8
```

------------------------------------------
    7. 하둡시작
    
```sh
    hdfs namenode -format
    start-dfs.sh
    start-yarn.sh
```
    8. Web GUI 확인

```sh    
    localhost:50070
    localhost:50090
```
    9. put a file ~

```sh    
    $ hdfs dfs -mkdir /user
    $ hdfs dfs -mkdir /user/hadoop
    $ hdfs dfs -put /var/log/boot.log
```

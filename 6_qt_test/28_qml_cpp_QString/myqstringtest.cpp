#include "myqstringtest.h"

QTextStream cout(stdout, QIODevice::WriteOnly);

MyQstringTest::MyQstringTest(QObject *parent) : QObject(parent)
{

}

// 使用 QList<QString> 建立一个list 数组；使用 QListIterator<QString> iter(list) 遍历取出数组
void MyQstringTest::myQListIterator()
{
    QString s1("Hello");
    QString s2("Qt");
    QList<QString> list;        // 定义元素是 QString 的list （数组）
    list << s1 << s2;

    // Java and STL like iterators
    QListIterator<QString> iter(list);  // 将list 放到迭代器中，使用 hasNext 判断是否有下一个，使用next 获取下一个（获取完后hasNext 往后加一）
    while(iter.hasNext()) {
        cout << iter.next();
        if (iter.hasNext()) {
            cout << " ";
        }
    }
    cout << "!" << endl;
}

// 使用 list.join
void MyQstringTest::myQlistJoin()
{
    QString s1("Hello");
    QString s2("Qt");
    QString s3("test");
    // convenient container classes
    QStringList list;
    list << s1 << s2 << s3;
    // join strings
    QString s = list.join(" ") + "!";       // join 所有子串中间都加入空格
    cout << s << endl;
}

// split 分割，for 循环
void MyQstringTest::myQstrintSplit()
{
    QString str = "0,1,2,3,4,5,6,7,8,9";
    QStringList  strs = str.split(",");     // 以 split 分割

    // foreach（variables ，Container）关键字是Qt对c++的一个扩展，主要用于按顺序历经容器（container）中的对象，
    // foreach用法类似于for循环，但是又有所不同，foreach可以使用一个变量名来遍历容器中的所有元素。
    // foreach宏的参数依次为：元素类型，元素名，容器类型，容器名。
//    foreach (QString s, strs)
//    {
//       int n =  s.toFloat();        // 将字符串转换成值
//       cout << " " << n ;
//    }
//    cout << endl;

// for 循环后的括号由冒号 “:” 分为两个部分：第一个部分用于表示循环的迭代变量，即当前变量的值；第二个部分用于表示被访问的（数组）集合。
    for (auto s : strs) {       // 新用法，foreach 将会被废弃
        cout << " " << s ;
    }
    cout << endl;
}

void MyQstringTest::myQTextStream()
{
    QList<QStringList> data;

    // file operations
    QFile file(":/test.txt");

    if(file.open(QIODevice::ReadOnly)) {    // 打开文件
        QTextStream stream(&file);          // 用流式读取文件
        // loop forever macro
        forever {
            QString line = stream.readLine();       // 读取一行
            // test for empty string 'QString("")'
//            if(line.isEmpty()) {
//                here();
//                continue;
//            }

            // test for null string 'String()'
            if(line.isNull()) {                     // 读到文件尾退出
                break;
            }
//            cout << line << endl;

            QStringList row;                                // QStringList  同 QList<QString>
            // for each loop to iterate over containers
            foreach(const QString& cell, line.split(",")) {
                row.append(cell.trimmed());

                here();
                for(QString s: row) {
                    cout << " " << s ;
                }
                cout << endl;
                here();
            }

            data.append(row);
        }
    }
}

//返回值为去除了开头和结尾的空白字符串，这里的空白指QChar::isSpace()返回值为true，比如'\t','\n','\v','\f','\r'和' ';
void MyQstringTest::mytrimmed()
{
    QString str = "  lots\t of\nwhitespace\r\n ";
    //str = str.trimmed();

    //返回字符串开头和结尾除去空白的字符串，并且内部的空白字符也去掉，这里的空白字符和上面的一样
    str = str.simplified();

    cout << str << endl;
}






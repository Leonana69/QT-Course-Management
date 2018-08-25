#include "enterWidget.h"
#include "my_course.h"
#include <QtWidgets/QApplication>

/*
 * Global variable
 */

extern char pw[PW_N];
extern vector<Course>courses; 		//全部课程 
extern vector<Student>students;		//全部学生
extern FILE *fd;					//文件


/*
 * Main
 */

int main(int argc, char *argv[])
{
    QApplication my_course_system(argc, argv);

	/*
	 * 初始化
	 */
	courses.clear();
	students.clear();

	if (!(fd = fopen("./my_data.mdt", "rb+")))
		//若不存在就创建一个 
	{
		qDebug("No file now, creat a file......\n");
		fd = fopen("./my_data.mdt", "wb+");
		strcpy(pw, "123456"); //默认初始密码
		save();
	}
	
	else
		/* 存在就读入数据 */
		read_information();

	/* 自动生成数据 */
	//generate_data();

	My_Course instance;
	instance.show();
    return my_course_system.exec();
}


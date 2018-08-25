#include "enterWidget.h"
#include "my_course.h"
#include <QtWidgets/QApplication>

/*
 * Global variable
 */

extern char pw[PW_N];
extern vector<Course>courses; 		//ȫ���γ� 
extern vector<Student>students;		//ȫ��ѧ��
extern FILE *fd;					//�ļ�


/*
 * Main
 */

int main(int argc, char *argv[])
{
    QApplication my_course_system(argc, argv);

	/*
	 * ��ʼ��
	 */
	courses.clear();
	students.clear();

	if (!(fd = fopen("./my_data.mdt", "rb+")))
		//�������ھʹ���һ�� 
	{
		qDebug("No file now, creat a file......\n");
		fd = fopen("./my_data.mdt", "wb+");
		strcpy(pw, "123456"); //Ĭ�ϳ�ʼ����
		save();
	}
	
	else
		/* ���ھͶ������� */
		read_information();

	/* �Զ��������� */
	//generate_data();

	My_Course instance;
	instance.show();
    return my_course_system.exec();
}


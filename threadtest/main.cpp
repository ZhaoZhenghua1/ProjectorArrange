
#include <QtCore/QCoreApplication>
#include <QThread>
#include <QVector>
#include <QMutex>
#include <QSemaphore>
#include <QWaitCondition>
#include <iostream>

QVector<int> storage;
QMutex mutex;
QSemaphore semaphoreUsed;
QSemaphore semaphoreUnUsed(100);
QWaitCondition wailCondition;

class Consumer : public QThread
{
public:
	virtual void run()override
	{
		while (1)
		{
			std::cout << 0;
			QMutexLocker locker(&mutex);
			wailCondition.wait(&mutex);
			if (storage.size() >= 5)
			{
				storage.removeFirst();
				storage.removeFirst();
				storage.removeFirst();
				storage.removeFirst();
				storage.removeFirst();
			}
			std::cout << 0;

		}
	}
};

class Product : public QThread
{
public:
	virtual void run()override
	{
		while (1)
		{
			QMutexLocker locker(&mutex);
			std::cout << 1;
			storage.push_back(0);
			std::cout << 1;
			if (storage.size() >= 5)
			{
				wailCondition.wakeAll();
			}
			
		}
	}
};

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	Consumer c;
	Product p;
	c.start();
	p.start();
	return a.exec();
}

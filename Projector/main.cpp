#include "projector.h"
#include <QtWidgets/QApplication>
#include "MainWindow.h"
#include <initializer_list>

int max(int A[], int l, int r) {
	if (l == r) {
		return A[l] > 0 ? A[l] : 0;
	}
	int mid = (l + r) / 2;
	int lms = max(A, l, mid);
	int rms = max(A, mid + 1, r);

	int maxLeft = 0, maxLTemp = 0;
	for (int i = mid; i >= l; --i) {
		maxLTemp += A[i];
		if (maxLTemp > maxLeft) {
			maxLeft = maxLTemp;
		}
	}
	int maxRight = 0, maxRTemp = 0;
	for (int i = mid + 1; i <= r; ++i) {
		maxRTemp += A[i];
		if (maxRTemp > maxRight) {
			maxRight = maxRTemp;
		}
	}
	return qMax(lms, qMax(rms, maxLeft + maxRight));
}

int main(int argc, char *argv[])
{
// 	int A[] = { 4,-3,5,2,-1,2,6,-2 };
// 	int ma = max(A, 0, 7);
	QApplication a(argc, argv);
	Projector w;
	w.show();
//	MainWindow mw;
//	mw.show();
	return a.exec();
}

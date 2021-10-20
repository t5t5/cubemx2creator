#include <QtTest/QTest>
#include <QDebug>
#include <QVariant>

class TestMakefile : public QObject
{
	Q_OBJECT
private slots:
	void test();
};

void TestMakefile::test()
{
}

QTEST_MAIN(TestMakefile)

#include "test_makefile.moc"

/*
    Copyright (C) 2010  Collabora Multimedia.
      @author Mauricio Piacentini <mauricio.piacentini@collabora.co.uk>

    This library is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "qgsttest.h"
#include <QGst/Clock>

class ClockTest : public QGstTest
{
    Q_OBJECT

private Q_SLOTS:
    void systemTest();
    void timeFromClockTimeTest();
    void clockTimeFromTimeTest();
};

void ClockTest::systemTest()
{
    QGst::ClockPtr sysclock = QGst::Clock::systemClock();

    QGst::ClockTime clocktime1 = sysclock->clockTime();
    QTime time1 = sysclock->time();
    QVERIFY(time1.isValid());

    QGst::ClockTime clocktime2 = sysclock->clockTime();
    QVERIFY(clocktime2 > clocktime1);
}

void ClockTest::timeFromClockTimeTest()
{
    QCOMPARE(QGst::Clock::timeFromClockTime(3600 * 1000 * 1000000LL).toString(),
             QString("01:00:00")); // 1 hour
    QCOMPARE(QGst::Clock::timeFromClockTime(4000 * 1000 * 1000000LL).toString(),
             QString("01:06:40"));
    QCOMPARE(QGst::Clock::timeFromClockTime(50001 * 1000 * 1000000LL).toString(),
             QString("13:53:21"));
    QCOMPARE(QGst::Clock::timeFromClockTime(120000 * 1000 * 1000000LL).toString(),
             QString("09:20:00")); // wraps
}

void ClockTest::clockTimeFromTimeTest()
{
    QCOMPARE(static_cast<quint64>(QGst::Clock::clockTimeFromTime(QTime(1, 0))),
             static_cast<quint64>(3600 * 1000 * 1000000LL)); // 1 hour

    QCOMPARE(static_cast<quint64>(QGst::Clock::clockTimeFromTime(QTime(1, 6, 40))),
             static_cast<quint64>(4000 * 1000 * 1000000LL));

    QCOMPARE(static_cast<quint64>(QGst::Clock::clockTimeFromTime(QTime(13, 53, 21, 15))),
             static_cast<quint64>((50001 * 1000 +15) * 1000000LL));
}


QTEST_MAIN(ClockTest)

#include "moc_qgsttest.cpp"
#include "clocktest.moc"


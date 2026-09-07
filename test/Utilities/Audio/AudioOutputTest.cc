/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "AudioOutputTest.h"
#include "AudioOutput.h"

#include <QtTest/QTest>

void AudioOutputTest::_testBracketedText()
{
    QCOMPARE(AudioOutput::_removeBracketedText(QStringLiteral("<E-210> 異常振動を検知しました")), QStringLiteral("異常振動を検知しました"));
    QCOMPARE(AudioOutput::_removeBracketedText(QStringLiteral("<E-301> Error <E-510> detected")), QStringLiteral("Error detected"));
    QCOMPARE(AudioOutput::_removeBracketedText(QStringLiteral("<E-210> <E-301> <E-510>")), QString());
    QCOMPARE(AudioOutput::_removeBracketedText(QStringLiteral("before<any content>after")), QStringLiteral("before after"));
    QCOMPARE(AudioOutput::_removeBracketedText(QStringLiteral("ESC Overheat")), QStringLiteral("ESC Overheat"));
    QCOMPARE(AudioOutput::_speechLocaleForText(AudioOutput::_removeBracketedText(QStringLiteral("<日本語> Error"))).language(), QLocale::English);
}

void AudioOutputTest::_testSpeechLocales()
{
    QCOMPARE(AudioOutput::_speechLocaleForText(QStringLiteral("<C-510> ESC温度が100℃を超過しました")).language(), QLocale::Japanese);
    QCOMPARE(AudioOutput::_speechLocaleForText(QStringLiteral("アームしないでください。")).language(), QLocale::Japanese);
    QCOMPARE(AudioOutput::_speechLocaleForText(QStringLiteral("異常振動")).language(), QLocale::Japanese);
    QCOMPARE(AudioOutput::_speechLocaleForText(QStringLiteral("<C-510> ESC Overheat")).language(), QLocale::English);
    QCOMPARE(AudioOutput::_speechLocaleForText(QStringLiteral("armed")).language(), QLocale::English);
}

void AudioOutputTest::_testSpokenReplacements()
{
    QString result = AudioOutput::_fixTextMessageForAudio(QStringLiteral("-10.5m, -10.5m. -10.5 m"));
    QCOMPARE(result, QStringLiteral("negative 10 point 5 meters, negative 10 point 5 meters. negative 10 point 5  meters"));
    result = AudioOutput::_fixTextMessageForAudio(QStringLiteral("-10m -10 m"));
    QCOMPARE(result, QStringLiteral("negative 10 meters negative 10  meters"));
    result = AudioOutput::_fixTextMessageForAudio(QStringLiteral("foo -10m -10 m bar"));
    QCOMPARE(result, QStringLiteral("foo negative 10 meters negative 10  meters bar"));
    result = AudioOutput::_fixTextMessageForAudio(QStringLiteral("-foom"));
    QCOMPARE(result, QStringLiteral("-foom"));
    result = AudioOutput::_fixTextMessageForAudio(QStringLiteral("10 moo"));
    QCOMPARE(result, QStringLiteral("10 moo"));
    result = AudioOutput::_fixTextMessageForAudio(QStringLiteral("10moo"));
    QCOMPARE(result, QStringLiteral("10moo"));
    result = AudioOutput::_fixTextMessageForAudio(QStringLiteral("10ms"));
    QCOMPARE(result, QStringLiteral("10ms"));
    result = AudioOutput::_fixTextMessageForAudio(QStringLiteral("1000ms"));
    QCOMPARE(result, QStringLiteral("1 second"));
    result = AudioOutput::_fixTextMessageForAudio(QStringLiteral("1001ms"));
    QCOMPARE(result, QStringLiteral("1 second and 1 millisecond"));
}

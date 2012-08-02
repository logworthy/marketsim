#ifndef INSTRUCTIONSCREENTEST2_H
#define INSTRUCTIONSCREENTEST2_H

#include <QWidget>

namespace Ui {
class InstructionScreenTest2;
}

class InstructionScreenTest2 : public QWidget
{
    Q_OBJECT
    
public:
    explicit InstructionScreenTest2(QWidget *parent = 0);
    ~InstructionScreenTest2();
    
private:
    Ui::InstructionScreenTest2 *ui;

signals:
    void        testPassed();

private slots:
    void updatePrices();
    void displayAllocation();
    void updateAllocation();
};

#endif // INSTRUCTIONSCREENTEST2_H

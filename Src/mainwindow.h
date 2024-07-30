#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <bitset>
#include <map>
#include <fstream>

using namespace std;
typedef bitset<16> reg;
typedef bitset<8> byte_reg;
#define RAM_SIZE 65536;



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    inline quint16 getPC() { return PC.to_ulong(); }
    inline quint16 getMDR() { return MDR.to_ulong(); }
    inline quint16 getMAR() { return MAR.to_ulong(); }
    inline quint16 getIR() { return IR.to_ulong(); }
    inline quint16 getN() { return Neg.to_ulong(); }
    inline quint16 getP() { return Pos.to_ulong(); }
    inline quint16 getZ() { return Zero.to_ulong(); }
    inline quint16 getReg(int index) { return regs[index].to_ulong(); }
    inline void setPC(const quint16& _PC) { PC = bitset<16>(_PC); }
    inline void setMAR(const quint16& _MAR) { MAR = bitset<16>(_MAR); }
    inline void setMDR(const quint16& _MDR) { MDR = bitset<16>(_MDR); }
    inline void setIR(const quint16& _IR) { IR = bitset<16>(_IR); }
    inline void setReg(const quint16& val,int reg_num) { this->regs[reg_num] = bitset<16>(val); }
    inline void incPC() { setPC(getPC()+1); }
    inline void incMAR() { setMAR(getMAR()+1); }
    inline void incMDR() { setMDR(getMDR()+1); }
    reg addressAdd(reg offset);
    void addressAdd(int base_reg,reg offset);
    void ALU_Add(int dest,int r1,int r2);
    void ALU_Add(int dest,int r1,bitset<5> immi);
    void ALU_And(int dest,int r1,int r2);
    void ALU_And(int dest,int r2,bitset<5> immi);
    void ALU_Not(int  dest,int source);
    void zeroExtend(byte_reg val);
    void regsReset();
    void resetRam();
    void printSPRegs();
    void printRegs();
    void printRam();
    bool isNumber(const QString& str);
    bool isReg(const QString& str);
    reg signExtend(bitset<6> val);

private slots:
    void on_resetButton_clicked();
    void on_compileButton_clicked();
    void on_runButton_clicked();
    void on_nxtButton_clicked();
    void on_gotoButton_clicked();
    void on_inputButton_clicked();

private:
    Ui::MainWindow *ui;
    reg ram[65536];
    reg PC,MAR,MDR,IR;
    reg regs[8];
    reg KBSR,KBDR;
    reg DSR,DDR;
    bitset<1> Neg,Zero,Pos;
    int clk = 0;
    int line = 0;
    bool compiled = false;
    bool reset = false;
    bool run = false;
    map<QString,int> secondTime;
    map<QString,int> firstTime;
    map<int,int> why;
    QStringList code;
    int lines;
    int mem = 0;

};
#endif // MAINWINDOW_H

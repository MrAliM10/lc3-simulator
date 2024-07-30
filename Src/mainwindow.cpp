#include "mainwindow.h"
#include "ui_mainwindow.h"


QString complement(QString str) {
    bool see = false;
    for(int i = str.size()-1 ; i >= 0 ; i--) {
        if(see) str[i] = str[i] == '1' ? '0' : '1';
        if(str[i] == '1' && see == false) see = true;
    }
    return str;
}

int myToInt(QString str,int base) {
    bool ok = true;
    if(str[0] == 0) {
        return str.toInt(&ok,2);
    }
    else {
        str = complement(str);
        return -1*str.toInt(&ok,2);
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->editor->setFocus();
    on_resetButton_clicked();

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::isNumber(const QString &str)
{
    for(auto chr : str.toStdString()) {
        if((chr >= 'a' && chr <= 'f') || (chr >= 'A' && chr <= 'F') || chr == '+' || chr == '-' || chr == '#' || chr == 'x' || chr == 'b')
            continue;
        else if(isdigit(chr) == 0) return false;
    }
    return true;
}

bool MainWindow::isReg(const QString &str)
{
    for(auto chr : str.toStdString()) {
        if(chr == 'R' || (chr >= '0' && chr <= '7') || chr == ',')
            continue;
        else return false;
    }
    return true;
}

void MainWindow::on_resetButton_clicked()
{
    reset = true;
    PC.reset();
    MAR.reset();
    MDR.reset();
    IR.reset();
    KBDR.reset();
    KBSR.reset();
    DDR.reset();
    DSR.set(15);
    Neg.reset();
    Zero.reset();
    Pos.reset();
    this->regsReset();
    this->resetRam();
    printRegs();
    printSPRegs();
    printRam();
    ui->console->setText("");
    ui->clock->setText("");
    this->line = 0;
    this->mem = 0x3000;
    clk = 0;
}

void MainWindow::regsReset()
{
    for(int i = 0 ; i < 8 ; i++) {
        regs[i].reset();
    }
}

void MainWindow::resetRam()
{
    for(int i = 0; i < 65536; i++) {
        ram[i].reset();
    }
}

void MainWindow::printSPRegs()
{
    ui->IRle->setText(QString::number(IR.to_ulong(), 16).toUpper());
    ui->PCle->setText(QString::number(PC.to_ulong(), 16).toUpper());
    ui->MARle->setText(QString::number(MAR.to_ulong(), 16).toUpper());
    ui->MDRle->setText(QString::number(MDR.to_ulong(), 16).toUpper());
    ui->Nle->setText(QString::number(Neg.to_ulong(), 16).toUpper());
    ui->Zle->setText(QString::number(Zero.to_ulong(), 16).toUpper());
    ui->Ple->setText(QString::number(Pos.to_ulong(), 16).toUpper());
    ui->KBDR_le->setText(QString::number(KBDR.to_ulong(),16).toUpper());
    ui->KBSR_le->setText(QString::number(KBSR.to_ulong(),16).toUpper());
    ui->DSR_le->setText(QString::number(DSR.to_ulong(),16).toUpper());
    ui->DDR_le->setText(QString::number(DDR.to_ulong(),16).toUpper());
}

void MainWindow::printRegs()
{
    ui->REGtw->setRowCount(0);
    for(int i = 0 ; i < 8 ; i++) {
        QString off = QString::number(i);
        QString name = QString::fromStdString("R") + off;
        QTableWidgetItem *itmName = new QTableWidgetItem();
        QTableWidgetItem *itmVal = new QTableWidgetItem();
        itmName->setText(name);
        itmVal->setText(QString::number(regs[i].to_ulong(),16).toUpper());
        ui->REGtw->insertRow(i);
        ui->REGtw->setItem(i,0,itmName);
        ui->REGtw->setItem(i,1,itmVal);
    }
}

void MainWindow::printRam()
{
    if(this->reset) {
        ui->RAMtw->setRowCount(0);
        for(int i = 0 ; i < 65024 ; i++) {
            QString addr = QString::number(i,16).toUpper();
            QTableWidgetItem *itmAddr = new QTableWidgetItem();
            QTableWidgetItem *itmVal = new QTableWidgetItem();
            itmAddr->setText(addr);
            itmVal->setText("0000");
            ui->RAMtw->insertRow(i);
            ui->RAMtw->setItem(i,1,itmAddr);
            ui->RAMtw->setItem(i,2,itmVal);
        }
        this->reset = false;
    }
    else {
        for(int i = 0 ; i < 65024 ; i++) {
            QString addr = QString::number(i,16).toUpper();
            QTableWidgetItem *itmAddr = new QTableWidgetItem();
            QTableWidgetItem *itmVal = new QTableWidgetItem();
            QString ramval = QString::number(ram[i].to_ulong(),16).toUpper();
            if(ramval.size()==3){
                ramval = "0" + ramval;
            }
            else if(ramval.size()==2){
                ramval = "00" + ramval;
            }
            else if(ramval.size()==1){
                ramval = "000" + ramval;
            }
            itmAddr->setText(addr);
            itmVal->setText(ramval);
            ui->RAMtw->setItem(i,1,itmAddr);
            ui->RAMtw->setItem(i,2,itmVal);
        }
    }
}


void MainWindow::on_compileButton_clicked()
{
    ui->nxtButton->setEnabled(true);
    ui->runButton->setEnabled(true);
    map<int,string> to_binary;
    to_binary[0] = "000";
    to_binary[1] = "001";
    to_binary[2] = "010";
    to_binary[3] = "011";
    to_binary[4] = "100";
    to_binary[5] = "101";
    to_binary[6] = "110";
    to_binary[7] = "111";
    this->on_resetButton_clicked();
    this->reset = false;
    this->compiled = true;
    int cnt = 0;
    ui->console->setText("Compiling...");
    code = ui->editor->toPlainText().split('\n',Qt::SkipEmptyParts);
    lines = code.size();
    bool end = false;
    for(int i = 0 ; i < lines ; i++) {
        if(cnt > 65536) {
            ui->console->setText("Memory has no available disk space");
            this->compiled = false;
            break;
        }
        if(code.at(i)[0] == ';') {
            continue;
        }
        QString code_line = code.at(i);
        qsizetype comment = code.at(i).indexOf(';');
        if(comment != -1)
            code_line = code_line.remove(comment,code_line.size());
        QStringList operation = code_line.split(' ',Qt::SkipEmptyParts);
        if(operation.at(0)[0] == ';' || operation.size() == 0) {
            continue;
        }
        if(operation.at(0)[operation.at(0).size()-1] == ',') {
            QString tmp = QString::fromStdString("");
            for(auto chr : operation.at(0)) {
                if(chr == ',') continue;
                tmp +=chr;
            }
            this->firstTime[tmp] = cnt;
        }
        else if(operation.at(0) == "ORG" ) {
            if(this->isNumber(operation.at(1)))
            {
                bool ok=1;
                cnt=operation.at(1).toInt(&ok,16);
                continue;

            }
            else
            {
                ui->console->setText("error in line:"+QString::number(i+1)+"\nafter ORG, hexdecimal number neaded. \n");
                compiled=0;
                break;
            }
        }
        this->why[cnt] = i;
        cnt++;
    }

    cnt = 0;

    for(int i = 0 ; i < lines ; i++) {
        bool lbl_flag = false;
        if(cnt > 65536) {
            ui->console->setText("Memory has no available disk space");
            this->compiled = false;
            break;
        }
        QString code_line = code.at(i);
        if(code_line[0] == ';') {
            continue;
        }
        qsizetype comment = code.at(i).indexOf(';');
        if(comment != -1)
            code_line = code_line.remove(comment,code_line.size());
        QStringList operation = code_line.split(' ',Qt::SkipEmptyParts);
        if(operation.at(0)[0] == ';' || operation.size() == 0) {
            continue;
        }
        else if(operation.at(0) == "ORG" ) {
            if(this->isNumber(operation.at(1)))
            {
                bool ok=1;
                cnt=operation.at(1).toInt(&ok,16);
                continue;

            }
            else
            {
                ui->console->setText("error in line:"+QString::number(i+1)+"\nafter ORG, hexdecimal number neaded. \n");
                compiled=0;
                break;
            }
        }
        else if(operation.at(0)[operation.at(0).size()-1] == ',') {
            QString tmp = QString::fromStdString("");
            for(auto chr : operation.at(0)) {
                if(chr == ',') continue;
                tmp +=chr;
            }
            this->secondTime[tmp] = i;
            QTableWidgetItem *lbl = new QTableWidgetItem();
            QTableWidgetItem *ins = new QTableWidgetItem();
            lbl->setText(tmp);
            ui->RAMtw->setItem(cnt,0,lbl);
            ins->setText(this->code.at(i));
            ui->RAMtw->setItem(cnt,3,ins);
            if(operation.at(1) == "DEC") {
                if(this->isNumber(operation.at(2))){
                    bool ok = true;
                    ram[cnt] = operation.at(2).toInt(&ok);
                    cnt++;
                    continue;
                }
                else {
                    ui->console->setText("error in line:"+QString::number(i+1)+"\nafter label, hexdecimal number neaded. \n");
                    compiled=0;
                    break;
                }
            }
            else if(operation.at(1) == "HEX") {
                if(this->isNumber(operation.at(2))){
                    bool ok = true;
                    ram[cnt] = operation.at(2).toInt(&ok,16);
                    cnt++;
                    continue;
                }
                else {
                    ui->console->setText("error in line:"+QString::number(i+1)+"\nafter label, hexdecimal number neaded. \n");
                    compiled=0;
                    break;
                }
            }
            else {
                for(int j = 0 ; j < operation.length()-1; j++) {
                    operation[j] = operation[j+1];
                }
                lbl_flag = true;
            }
        }
        if(operation.at(0) == "DEC") {
            QTableWidgetItem *ins = new QTableWidgetItem();
            ins->setText(this->code.at(i));
            ui->RAMtw->setItem(cnt,3,ins);
            if(operation.length() > 1 && this->isNumber(operation.at(1))){
                bool ok = true;
                ram[cnt] = operation.at(2).toInt(&ok,10);
                cnt++;
            }
            else {
                ui->console->setText("error in line:"+QString::number(i+1)+"\nafter label, hexdecimal number neaded. \n");
                compiled=0;
                break;
            }
        }
        else if(operation.at(0) == "HEX") {
            QTableWidgetItem *ins = new QTableWidgetItem();
            ins->setText(this->code.at(i));
            ui->RAMtw->setItem(cnt,3,ins);
            if(operation.length() > 1 && this->isNumber(operation.at(1))){
                bool ok = true;
                ram[cnt] = operation.at(2).toInt(&ok,16);
                cnt++;
            }
            else {
                ui->console->setText("error in line:"+QString::number(i+1)+"\nafter label, hexdecimal number neaded. \n");
                compiled=0;
                break;
            }
        }
        else if(operation.at(0) == "ADD") {
            QTableWidgetItem *ins = new QTableWidgetItem();
            ins->setText(this->code.at(i));
            ui->RAMtw->setItem(cnt,3,ins);
            int base = 10;
            if(((operation.size() ==5 && lbl_flag) || operation.size()== 4) && isReg(operation.at(1)) && isReg(operation.at(2))) {
                if(isNumber(operation.at(3))) {
                    bool ok = true;
                    bool flg = false;
                    QString str = QString::fromStdString("");
                    for(auto chr : operation.at(3)) {
                        if(chr == '-')
                            flg = true;
                        else if(chr == '#')
                            base = 10;
                        else if(chr == 'b')
                            base = 2;
                        else if(chr == 'x')
                            base = 16;
                        else
                            str += chr;
                    }
                    int immi = str.toInt(&ok,base);
                    if(immi > 15 || immi < -16) {
                        ui->console->setText("warning in line:"+QString::number(i+1)+"\nImmidiate number will be overflowed");
                        // compiled=0;
                        // break;
                    }
                    QString imm = QString::number(str.toInt(&ok,base),2);
                    if(imm.size()<5) {
                        QString add = QString::fromStdString("");
                        for(int i = 0 ; i < (5 - imm.size());i++) {
                            add +='0';
                        }
                        imm = add + imm;
                    }
                    if(flg) {
                        imm = complement(imm);
                    }
                    int dest = (operation.at(1)[1]).digitValue();
                    int source = (operation.at(2)[1]).digitValue();
                    reg val("0001"+to_binary[dest]+to_binary[source]+"1"+imm.toStdString());
                    ram[cnt] = val;
                }
                else if(isReg(operation.at(3))) {
                    int dest = (operation.at(1)[1]).digitValue();
                    int s1 = (operation.at(2)[1]).digitValue();
                    int s2 = (operation.at(3)[1]).digitValue();
                    reg val("0001"+to_binary[dest]+to_binary[s1]+"000"+to_binary[s2]);
                    ram[cnt] = val;
                }
                else {
                    ui->console->setText("error in line:"+QString::number(i+1)+"\n");
                    compiled=0;
                    break;
                }
            }
            else if(operation.size() < 4 || operation.size() > 4) {
                ui->console->setText("error in line:"+QString::number(i+1)+"\nPlease put space between each argument");
                compiled=0;
                break;
            }

        }
        else if(operation.at(0) == "AND") {
            QTableWidgetItem *ins = new QTableWidgetItem();
            ins->setText(this->code.at(i));
            ui->RAMtw->setItem(cnt,3,ins);
            if(((operation.size() == 5 && lbl_flag) || operation.size()== 4) && isReg(operation.at(1)) && isReg(operation.at(2))) {
                if(isNumber(operation.at(3))) {
                    bool ok = true;
                    bool flg = false;
                    int base = 10;
                    QString str = QString::fromStdString("");
                    for(auto chr : operation.at(3)) {
                        if(chr == '-')
                            flg = true;
                        else if(chr == '#')
                            base = 10;
                        else if(chr == 'b')
                            base = 2;
                        else if(chr == 'x')
                            base = 16;
                        else
                            str +=chr;
                    }
                    int immi = str.toInt(&ok,base );
                    if(immi > 15 || immi < -16) {
                        ui->console->setText("warning in line:"+QString::number(i+1)+"\nImmidiate number will be overflowed");
                        // compiled=0;
                        // break;
                    }
                    QString imm = QString::number(str.toInt(&ok,base),2);
                    if(imm.size()<5) {
                        QString add = QString::fromStdString("");
                        for(int i = 0 ; i < (5 - imm.size());i++) {
                            add +='0';
                        }
                        imm = add + imm;
                    }
                    if(flg) {
                        imm = complement(imm);
                    }
                    int dest = (operation.at(1)[1]).digitValue();
                    int source = (operation.at(2)[1]).digitValue();
                    reg val("0101"+to_binary[dest]+to_binary[source]+"1"+imm.toStdString());
                    ram[cnt] = val;
                }
                else if(isReg(operation.at(3))) {
                    int dest = (operation.at(1)[1]).digitValue();
                    int s1 = (operation.at(2)[1]).digitValue();
                    int s2 = (operation.at(3)[1]).digitValue();
                    reg val("0101"+to_binary[dest]+to_binary[s1]+"000"+to_binary[s2]);
                    ram[cnt] = val;
                }
                else {
                    ui->console->setText("error in line:"+QString::number(i+1)+"\n");
                    compiled=0;
                    break;
                }
            }
            else if(operation.size() < 4) {
                ui->console->setText("error in line:"+QString::number(i+1)+"\nPlease put space between each argument");
                compiled=0;
                break;
            }
        }
        else if(operation.at(0) == "NOT") {
            QTableWidgetItem *ins = new QTableWidgetItem();
            ins->setText(this->code.at(i));
            ui->RAMtw->setItem(cnt,3,ins);
            if(operation.size()== 3 && isReg(operation.at(1)) && isReg(operation.at(2))) {
                int dest = (operation.at(1)[1]).digitValue();
                int source = (operation.at(2)[1]).digitValue();
                reg val("1001"+to_binary[dest]+to_binary[source]+"111111");
                ram[cnt] = val;
            }
            else if(operation.size() < 3) {
                ui->console->setText("error in line:"+QString::number(i+1)+"\nPlease put space between each argument");
                compiled=0;
                break;
            }
            else {
                ui->console->setText("error in line:"+QString::number(i+1)+"\nMay you have enter wrong name for register");
                compiled=0;
                break;
            }
        }
        else if(operation.at(0) == "LD") {
            QTableWidgetItem *ins = new QTableWidgetItem();
            ins->setText(this->code.at(i));
            ui->RAMtw->setItem(cnt,3,ins);
            if(operation.size() < 3) {
                ui->console->setText("error in line:"+QString::number(i+1)+"\nPlease put space between each argument");
                compiled=0;
                break;
            }
            if(this->firstTime[operation.at(2)] == 0 && isNumber(operation.at(2))){
                ui->console->setText("error in line:"+QString::number(i+1)+"\nThis label isn't exist");
                compiled=0;
                break;
            }
            if(((operation.size() == 4 && lbl_flag) || operation.size()== 3) && isReg(operation.at(1))) {
                if(this->firstTime[operation.at(2)] != 0) {
                    int dest = (operation.at(1)[1]).digitValue();
                    int len = firstTime[operation.at(2)] - cnt - 1;
                    QString str = QString::number(len,2);
                    if(str.size() < 9) {
                        QString add = QString::fromStdString("");
                        for(int i = 0 ; i < (9 - str.size());i++) {
                            add +='0';
                        }
                        str = add + str;
                    }
                    reg val("0010"+to_binary[dest]+str.toStdString());
                    ram[cnt] = val;
                }
                else if(isNumber(operation.at(2))) {
                    bool ok = true;
                    bool flg = false;
                    int base = 10;
                    QString str = QString::fromStdString("");
                    for(auto chr : operation.at(2)) {
                        if(chr == '-')
                            flg = true;
                        else if(chr == '#')
                            base = 10;
                        else if(chr == 'b')
                            base = 2;
                        else if(chr == 'x')
                            base = 16;
                        else
                            str += chr;
                    }
                    int immi = str.toInt(&ok,base);
                    if(immi > 255 || immi < -256) {
                        ui->console->setText("warning in line:"+QString::number(i+1)+"\nImmidiate number will be overflowed");
                        // compiled=0;
                        // break;
                    }
                    QString imm = QString::number(str.toInt(&ok,base),2);
                    if(imm.size()<9) {
                        QString add = QString::fromStdString("");
                        for(int i = 0 ; i < (9 - imm.size());i++) {
                            add +='0';
                        }
                        imm = add + imm;
                    }
                    if(flg) {
                        imm = complement(imm);
                    }
                    int dest = (operation.at(1)[1]).digitValue();
                    reg val("0010"+to_binary[dest]+imm.toStdString());
                    ram[cnt] = val;


                }
            }
            else {
                ui->console->setText("error in line:"+QString::number(i+1)+"\nMay you have enter wrong name for register");
                compiled=0;
                break;
            }
        }
        else if(operation.at(0) == "LDI") {
            QTableWidgetItem *ins = new QTableWidgetItem();
            ins->setText(this->code.at(i));
            ui->RAMtw->setItem(cnt,3,ins);
            if(operation.size() < 3) {
                ui->console->setText("error in line:"+QString::number(i+1)+"\nPlease put space between each argument");
                compiled=0;
                break;
            }
            if(this->firstTime[operation.at(2)] == 0){
                ui->console->setText("error in line:"+QString::number(i+1)+"\nThis label isn't exist");
                compiled=0;
                break;
            }
            if(((operation.size() == 4 && lbl_flag) || operation.size()== 3) && isReg(operation.at(1))) {
                if(this->firstTime[operation.at(2)] != 0) {
                    int dest = (operation.at(1)[1]).digitValue();
                    int len = firstTime[operation.at(2)] - cnt - 1;
                    QString str = QString::number(len,2);
                    if(str.size() < 9) {
                        QString add = QString::fromStdString("");
                        for(int i = 0 ; i < (9 - str.size());i++) {
                            add += '0';
                        }
                        str = add + str;
                    }
                    reg val("1010"+to_binary[dest]+str.toStdString());
                    ram[cnt] = val;
                }
                else if(isNumber(operation.at(2))) {
                    bool ok = true;
                    bool flg = false;
                    int base = 10;
                    QString str = QString::fromStdString("");
                    for(auto chr : operation.at(2)) {
                        if(chr == '-')
                            flg = true;
                        else if(chr == '#')
                            base = 10;
                        else if(chr == 'b')
                            base = 2;
                        else if(chr == 'x')
                            base = 16;
                        else
                            str += chr;
                    }
                    int immi = str.toInt(&ok,base);
                    if(immi > 255 || immi < -256) {
                        ui->console->setText("warning in line:"+QString::number(i+1)+"\nImmidiate number will be overflowed");
                        // compiled=0;
                        // break;
                    }
                    QString imm = QString::number(str.toInt(&ok,base),2);
                    if(imm.size()<9) {
                        QString add = QString::fromStdString("");
                        for(int i = 0 ; i < (9 - imm.size());i++) {
                            add +='0';
                        }
                        imm = add + imm;
                    }
                    if(flg) {
                        imm = complement(imm);
                    }
                    int dest = (operation.at(1)[1]).digitValue();
                    reg val("1010"+to_binary[dest]+imm.toStdString());
                    ram[cnt] = val;


                }
            }
            else {
                ui->console->setText("error in line:"+QString::number(i+1)+"\nMay you have enter wrong name for register");
                compiled=0;
                break;
            }
        }
        else if(operation.at(0) == "LDR") {
            QTableWidgetItem *ins = new QTableWidgetItem();
            ins->setText(this->code.at(i));
            ui->RAMtw->setItem(cnt,3,ins);
            if(((operation.size() == 4 && lbl_flag) || operation.size()== 4)&& isReg(operation.at(1)) && isReg(operation.at(2))) {
                if(isNumber(operation.at(3))) {
                    bool ok = true;
                    bool flg = false;
                    int base = 10;
                    QString str = QString::fromStdString("");
                    for(auto chr : operation.at(3)) {
                        if(chr == '-')
                            flg = true;
                        else if(chr == '#')
                            base = 10;
                        else if(chr == 'b')
                            base = 2;
                        else if(chr == 'x')
                            base = 16;
                        else
                            str += chr;
                    }
                    int immi = str.toInt(&ok,base);
                    if(immi > 31 || immi < -32) {
                        ui->console->setText("warning in line:"+QString::number(i+1)+"\nImmidiate number will be overflowed");
                        // compiled=0;
                        // break;
                    }
                    QString imm = QString::number(str.toInt(&ok,base),2);
                    if(imm.size()<6) {
                        QString add = QString::fromStdString("");
                        for(int i = 0 ; i < (6 - imm.size());i++) {
                            add +='0';
                        }
                        imm = add + imm;
                    }
                    if(flg) {
                        imm = complement(imm);
                    }
                    int dest = (operation.at(1)[1]).digitValue();
                    int source = (operation.at(2)[1]).digitValue();
                    reg val("0110"+to_binary[dest]+to_binary[source]+imm.toStdString());
                    ram[cnt] = val;
                }
                else {
                    ui->console->setText("error in line:"+QString::number(i+1)+"\n");
                    compiled=0;
                    break;
                }
            }
            else if(operation.size() < 4) {
                ui->console->setText("error in line:"+QString::number(i+1)+"\nPlease put space between each argument");
                compiled=0;
                break;
            }
        }
        else if(operation.at(0) == "LEA") {
            QTableWidgetItem *ins = new QTableWidgetItem();
            ins->setText(this->code.at(i));
            ui->RAMtw->setItem(cnt,3,ins);
            if(this->firstTime[operation.at(2)] == 0){
                ui->console->setText("error in line:"+QString::number(i+1)+"\nThis label isn't exist");
                compiled=0;
                break;
            }
            if(((operation.size() == 4 && lbl_flag) || operation.size()== 3) && isReg(operation.at(1))) {
                if(this->firstTime[operation.at(2)] != 0) {
                    int dest = (operation.at(1)[1]).digitValue();
                    int len = firstTime[operation.at(2)] - cnt - 1;
                    QString str = QString::number(len,2);
                    if(str.size() < 9) {
                        QString add = QString::fromStdString("");
                        for(int i = 0 ; i < (9 - str.size());i++) {
                            add +='0';
                        }
                        str = add + str;
                    }
                    reg val("1110"+to_binary[dest]+str.toStdString());
                    ram[cnt] = val;
                }
                else if(isNumber(operation.at(2))) {
                    bool ok = true;
                    bool flg = false;
                    int base = 10;
                    QString str = QString::fromStdString("");
                    for(auto chr : operation.at(2)) {
                        if(chr == '-')
                            flg = true;
                        else if(chr == '#')
                            base = 10;
                        else if(chr == 'b')
                            base = 2;
                        else if(chr == 'x')
                            base = 16;
                        else
                            str += chr;
                    }
                    int immi = str.toInt(&ok,base);
                    if(immi > 255 || immi < -256) {
                        ui->console->setText("warning in line:"+QString::number(i+1)+"\nImmidiate number will be overflowed");
                        // compiled=0;
                        // break;
                    }
                    QString imm = QString::number(str.toInt(&ok,base),2);
                    if(imm.size()<9) {
                        QString add = QString::fromStdString("");
                        for(int i = 0 ; i < (9 - imm.size());i++) {
                            add +='0';
                        }
                        imm = add + imm;
                    }
                    if(flg) {
                        imm = complement(imm);
                    }
                    int dest = (operation.at(1)[1]).digitValue();
                    reg val("1110"+to_binary[dest]+imm.toStdString());
                    ram[cnt] = val;
                }
                else if(operation.size() < 3) {
                    ui->console->setText("error in line:"+QString::number(i+1)+"\nPlease put space between each argument");
                    compiled=0;
                    break;
                }
                else {
                    ui->console->setText("error in line:"+QString::number(i+1)+"\nMay you have enter wrong name for register");
                    compiled=0;
                    break;
                }
            }

        }
        else if(operation.at(0) == "ST") {
            QTableWidgetItem *ins = new QTableWidgetItem();
            ins->setText(this->code.at(i));
            ui->RAMtw->setItem(cnt,3,ins);
            if(this->firstTime[operation.at(2)] == 0 && isNumber(operation.at(2))){
                ui->console->setText("error in line:"+QString::number(i+1)+"\nThis label isn't exist");
                compiled=0;
                break;
            }
            if(((operation.size() > 4 && lbl_flag) || operation.size()== 3) && isReg(operation.at(1))) {
                if(this->firstTime[operation.at(2)] != 0) {
                    int dest = (operation.at(1)[1]).digitValue();
                    int len = firstTime[operation.at(2)] - cnt - 1;
                    QString str = QString::number(len,2);
                    if(str.size() < 9) {
                        QString add = QString::fromStdString("");
                        for(int i = 0 ; i < (9 - str.size());i++) {
                            add +='0';
                        }
                        str = add + str;
                    }
                    reg val("0011"+to_binary[dest]+str.toStdString());
                    ram[cnt] = val;
                }
                else if(isNumber(operation.at(2))) {
                    bool ok = true;
                    bool flg = false;
                    int base = 10;
                    QString str = QString::fromStdString("");
                    for(auto chr : operation.at(2)) {
                        if(chr == '-')
                            flg = true;
                        else if(chr == '#')
                            base = 10;
                        else if(chr == 'b')
                            base = 2;
                        else if(chr == 'x')
                            base = 16;
                        else
                            str += chr;
                    }
                    int immi = str.toInt(&ok,base);
                    if(immi > 255 || immi < -256) {
                        ui->console->setText("warning in line:"+QString::number(i+1)+"\nImmidiate number will be overflowed");
                        // compiled=0;
                        // break;
                    }
                    QString imm = QString::number(str.toInt(&ok,base),2);
                    if(imm.size()<9) {
                        QString add = QString::fromStdString("");
                        for(int i = 0 ; i < (9 - imm.size());i++) {
                            add +='0';
                        }
                        imm = add + imm;
                    }
                    if(flg) {
                        imm = complement(imm);
                    }
                    int dest = (operation.at(1)[1]).digitValue();
                    reg val("0011"+to_binary[dest]+imm.toStdString());
                    ram[cnt] = val;
                }
                else if(operation.size() < 3) {
                    ui->console->setText("error in line:"+QString::number(i+1)+"\nPlease put space between each argument");
                    compiled=0;
                    break;
                }
                else {
                    ui->console->setText("error in line:"+QString::number(i+1)+"\nMay you have enter wrong name for register");
                    compiled=0;
                    break;
                }
            }
        }
        else if(operation.at(0) == "STI") {
            QTableWidgetItem *ins = new QTableWidgetItem();
            ins->setText(this->code.at(i));
            ui->RAMtw->setItem(cnt,3,ins);
            if(this->firstTime[operation.at(2)] == 0){
                ui->console->setText("error in line:"+QString::number(i+1)+"\nThis label isn't exist");
                compiled=0;
                break;
            }
            if(((operation.size() > 4 && lbl_flag) || operation.size()== 3) && isReg(operation.at(1))) {
                if(this->firstTime[operation.at(2)] != 0) {
                    int dest = (operation.at(1)[1]).digitValue();
                    int len = firstTime[operation.at(2)] - cnt - 1;
                    QString str = QString::number(len,2);
                    if(str.size() < 9) {
                        QString add = QString::fromStdString("");
                        for(int i = 0 ; i < (9 - str.size());i++) {
                            add +='0';
                        }
                        str = add + str;
                    }
                    reg val("1011"+to_binary[dest]+str.toStdString());
                    ram[cnt] = val;
                }
                else if(isNumber(operation.at(2))) {
                    bool ok = true;
                    bool flg = false;
                    int base = 10;
                    QString str = QString::fromStdString("");
                    for(auto chr : operation.at(2)) {
                        if(chr == '-')
                            flg = true;
                        else if(chr == '#')
                            base = 10;
                        else if(chr == 'b')
                            base = 2;
                        else if(chr == 'x')
                            base = 16;
                        else
                            str += chr;
                    }
                    int immi = str.toInt(&ok,base);
                    if(immi > 255 || immi < -256) {
                        ui->console->setText("warning in line:"+QString::number(i+1)+"\nImmidiate number will be overflowed");
                        // compiled=0;
                        // break;
                    }
                    QString imm = QString::number(str.toInt(&ok,base),2);
                    if(imm.size()<9) {
                        QString add = QString::fromStdString("");
                        for(int i = 0 ; i < (9 - imm.size());i++) {
                            add +='0';
                        }
                        imm = add + imm;
                    }
                    if(flg) {
                        imm = complement(imm);
                    }
                    int dest = (operation.at(1)[1]).digitValue();
                    reg val("1011"+to_binary[dest]+imm.toStdString());
                    ram[cnt] = val;
                }
                else if(operation.size() < 3) {
                    ui->console->setText("error in line:"+QString::number(i+1)+"\nPlease put space between each argument");
                    compiled=0;
                    break;
                }
                else {
                    ui->console->setText("error in line:"+QString::number(i+1)+"\nMay you have enter wrong name for register");
                    compiled=0;
                    break;
                }
            }
        }
        else if(operation.at(0) == "LDR") {
            QTableWidgetItem *ins = new QTableWidgetItem();
            ins->setText(this->code.at(i));
            ui->RAMtw->setItem(cnt,3,ins);
            if(((operation.size() > 4 && lbl_flag) || operation.size()== 4) && isReg(operation.at(1)) && isReg(operation.at(2))) {
                if(isNumber(operation.at(3))) {
                    bool ok = true;
                    bool flg = false;
                    int base = 10;
                    QString str = QString::fromStdString("");
                    for(auto chr : operation.at(3)) {
                        if(chr == '-')
                            flg = true;
                        else if(chr == '#')
                            base = 10;
                        else if(chr == 'b')
                            base = 2;
                        else if(chr == 'x')
                            base = 16;
                    }
                    int immi = str.toInt(&ok,base);
                    if(immi > 63 || immi < -64) {
                        ui->console->setText("error in line:"+QString::number(i+1)+"\nImmidiate number is to low or to short");
                        compiled=0;
                        break;
                    }
                    QString imm = QString::number(str.toInt(&ok,base),2);
                    if(imm.size()<6) {
                        QString add = QString::fromStdString("");
                        for(int i = 0 ; i < (6 - imm.size());i++) {
                            add +='0';
                        }
                        imm = add + imm;
                    }
                    if(flg) {
                        imm = complement(imm);
                    }
                    int dest = (operation.at(1)[1]).digitValue();
                    int source = (operation.at(2)[1]).digitValue();
                    reg val("0110"+to_binary[dest]+to_binary[source]+imm.toStdString());
                    ram[cnt] = val;
                }
                else {
                    ui->console->setText("error in line:"+QString::number(i+1)+"\n");
                    compiled=0;
                    break;
                }
            }
            else if(operation.size() < 4) {
                ui->console->setText("error in line:"+QString::number(i+1)+"\nPlease put space between each argument");
                compiled=0;
                break;
            }
        }
        else if(operation.at(0).startsWith("BR")) {
            QTableWidgetItem *ins = new QTableWidgetItem();
            ins->setText(this->code.at(i));
            ui->RAMtw->setItem(cnt,3,ins);
            if(operation.size() != 2) {
                ui->console->setText("error in line:"+QString::number(i+1)+"\nMay some of argument is missed!");
                compiled=0;
                break;
            }
            if(this->firstTime[operation.at(1)] == 0){
                ui->console->setText("error in line:"+QString::number(i+1)+"\nThis label isn't exist");
                compiled=0;
                break;
            }
            string n = "0",z = "0", p = "0";
            QString str = QString::fromStdString("");
            if(this->firstTime[operation.at(1)] != 0) {
                int len = firstTime[operation.at(1)] - cnt - 1;
                str = QString::number(len,2);
                if(str.size() < 9) {
                    QString add = QString::fromStdString("");
                    for(int i = 0 ; i < (9 - str.size());i++) {
                        add +='0';
                    }
                    str = add + str;
                }
                if(len < 0)
                    str = complement(str);
            }
            else if(isNumber(operation.at(1))) {
                bool ok = true;
                bool flg = false;
                int base = 10;
                for(auto chr : operation.at(1)) {
                    if(chr == '-')
                        flg = true;
                    else if(chr == '#')
                        base = 10;
                    else if(chr == 'b')
                        base = 2;
                    else if(chr == 'x')
                        base = 16;
                    else
                        str += chr;
                }
                int immi = str.toInt(&ok,base);
                if(immi > 255 || immi < -256) {
                    ui->console->setText("warning in line:"+QString::number(i+1)+"\nImmidiate number will be overflowed");
                    // compiled=0;
                    // break;
                }
                QString imm = QString::number(str.toInt(&ok,base),2);
                if(imm.size()<9) {
                    QString add = QString::fromStdString("");
                    for(int i = 0 ; i < (9 - imm.size());i++) {
                        add +='0';
                    }
                    imm = add + imm;
                }
                if(flg) {
                    imm = complement(imm);
                }
                str = imm;
            }
            if(operation.size() == 2) {
                if(operation.at(0) == "BR") {
                    reg val("0000000"+str.toStdString());
                    ram[cnt] = val;
                }
                else {
                    for(int j = 2 ; j < operation.at(0).size() ; j++) {
                        if(operation.at(0)[j] == 'n')
                            n = "1";
                        else if(operation.at(0)[j] == 'z')
                            z = "1";
                        else if(operation.at(0)[j] == 'p')
                            p = "1";
                    }
                    reg val("0000"+n+z+p+str.toStdString());
                    ram[cnt] = val;
                }
            }
        }
        else if(operation.at(0) == "JMP") {
            QTableWidgetItem *ins = new QTableWidgetItem();
            ins->setText(this->code.at(i));
            ui->RAMtw->setItem(cnt,3,ins);
            if(operation.size() != 2 && lbl_flag == false) {
                ui->console->setText("error in line:"+QString::number(i+1)+"\nMay some of argument is missed!");
                compiled=0;
                break;
            }
            else if(lbl_flag == true && operation.size() == 3) {
                if(isReg(operation.at(1))) {
                    ui->console->setText("error in line:"+QString::number(i+1)+"\nMay you have enter wrong name for register");
                    compiled=0;
                    break;
                }
                else {
                    int dest = (operation.at(1)[1]).digitValue();
                    reg val("1100000"+to_binary[dest]+"000000");
                    ram[cnt] = val;
                }
            }
        }
        else if(operation.at(0) == "RET") {
            QTableWidgetItem *ins = new QTableWidgetItem();
            ins->setText(this->code.at(i));
            ui->RAMtw->setItem(cnt,3,ins);
            if(operation.size() != 1 && lbl_flag == false) {
                ui->console->setText("error in line:"+QString::number(i+1)+"\nMay some of argument is missed!");
                compiled=0;
                break;
            }
            else if(lbl_flag == true && operation.size() == 2) {
                reg val("1100000111000000");
                ram[cnt] = val;
            }
        }
        else if(operation.at(0) == "JSR") {
            QTableWidgetItem *ins = new QTableWidgetItem();
            ins->setText(this->code.at(i));
            ui->RAMtw->setItem(cnt,3,ins);
            if(operation.size() != 2 && lbl_flag == false) {
                ui->console->setText("error in line:"+QString::number(i+1)+"\nMay some of argument is missed!");
                compiled=0;
                break;
            }
            if(lbl_flag && operation.size() != 3) {
                ui->console->setText("error in line:"+QString::number(i+1)+"\nMay some of argument is missed!");
                compiled=0;
                break;
            }
            if(this->firstTime[operation.at(1)] == 0){
                ui->console->setText("error in line:"+QString::number(i+1)+"\nThis label isn't exist");
                compiled=0;
                break;
            }
            QString str = QString::number(firstTime[operation.at(1)],2);
            if(str.size() < 11) {
                QString add = QString::fromStdString("");
                for(int i = 0 ; i < (11 - str.size());i++) {
                    add +=str[str.size()-1];
                }
                str = add + str;
            }
            reg val("01001"+str.toStdString());
            ram[cnt] = val;
        }
        else if(operation.at(0) == "JSRR") {
            QTableWidgetItem *ins = new QTableWidgetItem();
            ins->setText(this->code.at(i));
            ui->RAMtw->setItem(cnt,3,ins);
            if(operation.size() != 2) {
                ui->console->setText("error in line:"+QString::number(i+1)+"\nMay some of argument is missed!");
                compiled=0;
                break;
            }
            if(isReg(operation.at(1))){
                ui->console->setText("error in line:"+QString::number(i+1)+"\nMay you have enter wrong name for register");
                compiled=0;
                break;
            }
            int dest = (operation.at(1)[1]).digitValue();
            reg val("0010000"+to_binary[dest]+"000000");
            ram[cnt] = val;
        }
        else if(operation.at(0) == "HALT") {
            QTableWidgetItem *ins = new QTableWidgetItem();
            ins->setText(this->code.at(i));
            ui->RAMtw->setItem(cnt,3,ins);
            ram[cnt] = 0xFFFF;
        }
        else if(operation.at(0) == "END") {
            end=true;
            printRam();
            if(compiled)
            {
                ui->console->setText("Program successfully compiled!\n");
            }
            else
            {
                //ui->console->append("\nOPPS compile error!!\n");
            }
            break;
        }
        else {
            ui->console->setText("error in line:"+QString::number(i+1)+"\n");
            //ui->console->append(code.at(i));
            compiled=0;
            break;
        }
        cnt++;
    }
    if(!end && compiled)
    {
        ui->console->setText("Missing End psuedo operation\n");
        compiled=0;
    }
    else {
        ofstream wp("memory.bin", ios::out | ios::binary);
        if(!wp) {
            ui->console->setText("Cannot open memory.bin file!\nNote: program cannot be compiled!");
            compiled = 0;
            return;
        }
        for(int i = 0 ; i < lines ; i++) {
            wp << ram[i].to_string();
            wp << '\n';
        }
    }

}

void MainWindow::on_runButton_clicked()
{
    if(this->compiled == false) {
        ui->console->setText("Please first compile your code!");
    }
    else {
        this->run = true;
        while(run) {
            this->on_nxtButton_clicked();
        }
    }

}

void MainWindow::ALU_Add(int dest, int r1, bitset<5> immi)
{
    bitset<1> carry(0);
    reg sum(0);
    reg sec(0);
    if(immi.test(4)) {
        for(int i = 0 ; i < immi.size() ; i++) {
            sec[i] = immi[i];
        }
        for(int i = immi.size() ; i < sec.size() ; i++) {
            sec.set(i);
        }
    }
    else {
        for(int i = 0 ; i < immi.size() ; i++) {
            sec[i] = immi[i];
        }
    }

    for(int i = 0 ; i < sum.size() ; i++) {
        sum[i] = regs[r1][i] ^ sec[i] ^ carry[0];
        carry[0] = carry[0] & (regs[r1][i] ^ sec[i]) | (regs[r1][i] & sec[i]);
    }
    if(sum.test(15)) {
        this->Neg.set();
    }
    else if(sum.none()) {
        this->Zero.set();
    }
    else {
        this->Pos.set();
    }
    regs[dest] = sum;
}

void MainWindow::ALU_Add(int dest, int r1, int r2)
{
    bitset<1> carry(0);
    reg sum(0);
    for(int i = 0 ; i < sum.size() ; i++) {
        sum[i] = regs[r1][i] ^ regs[r2][i] ^ carry[0];
        carry[0] = carry[0] & (regs[r1][i] ^ regs[r2][i]) | (regs[r1][i] & regs[r2][i]);
    }
    if(sum.test(15)) {
        this->Neg.set();
    }
    else if(sum.none()) {
        this->Zero.set();
    }
    else {
        this->Pos.set();
    }
    regs[dest] = sum;
}

void MainWindow::ALU_And(int dest,int r2, bitset<5> immi)
{
    reg sec(0);
    if(immi.test(4)) {
        for(int i = 0 ; i < immi.size() ; i++) {
            sec[i] = immi[i];
        }
        for(int i = immi.size() ; i < sec.size() ; i++) {
            sec.set(i);
        }
    }
    else {
        for(int i = 0 ; i < immi.size() ; i++) {
            sec[i] = immi[i];
        }
    }
    regs[dest] = regs[r2] & sec;
    if(regs[dest].test(15)) {
        this->Neg.set();
    }
    else if(regs[dest].none()) {
        this->Zero.set();
    }
    else {
        this->Pos.set();
    }
}

void MainWindow::ALU_And(int dest, int r1, int r2)
{
    regs[dest] = regs[r2] & regs[r1];
    if(regs[dest].test(15)) {
        this->Neg.set();
    }
    else if(regs[dest].none()) {
        this->Zero.set();
    }
    else {
        this->Pos.set();
    }
}

void MainWindow::ALU_Not(int dest,int source) {
    regs[dest] = ~regs[source];
    if(regs[dest].test(15)) {
        this->Neg.set();
    }
    else if(regs[dest].none()) {
        this->Zero.set();
    }
    else {
        this->Pos.set();
    }
}

reg MainWindow::addressAdd(reg offset) {
    bitset<1> carry(0);
    reg sum(0);
    for(int i = 0 ; i < sum.size() ; i++) {
        sum[i] = PC[i] ^ offset[i] ^ carry[0];
        carry[0] = carry[0] & (PC[i] ^ offset[i]) | (PC[i] & offset[i]);
    }
    return sum;
    // MAR = sum;
}

void MainWindow::addressAdd(int base_reg, reg offset)
{
    bitset<1> carry(0);
    reg sum(0);
    for(int i = 0 ; i < sum.size() ; i++) {
        sum[i] = regs[base_reg][i] ^ offset[i] ^ carry[0];
        carry[0] = carry[0] & (regs[base_reg][i] ^ offset[i]) | (regs[base_reg][i] & offset[i]);
    }
    MAR = sum;
}

reg MainWindow::signExtend(bitset<6> val)
{
    reg out(0);
    for(int i = 0 ; i < 6 ; i++) {
        out[i] = out[i] | val[i];
    }
    if(val.test(5)) {
        out |= 0xFFC0;
    }
    return out;
}

void MainWindow::on_nxtButton_clicked()
{
    if(this->compiled == false) {
        ui->console->setText("Please, at first compile your code!");
        return;
    }
    ui->console->setText("");
    if(compiled == false) {
        ui->console->setText("Please make sure your code had compiled first");
    }
    else {
        if(DSR.test(15) == false) {
            ui->output_le->setText(QString::number(DDR.to_ulong(),10));
            ui->console->setText("I/O processed data and successfully shown it");
            this->DSR.set(15);
        }
        ui->RAMtw->selectRow(mem-1);
        QStringList operation = code.at(line).split(' ', Qt::SkipEmptyParts);
        if(operation.at(0) == ';') line++;
        else if(operation.at(0) == "ORG") {
            bool ok = 1;
            // mem = operation.at(1).toInt(&ok,16);
            line++;
        }
        operation = code.at(line).split(' ',Qt::SkipEmptyParts);
        if(clk == 0) {
            PC = mem;
            MAR = PC;
            this->incPC();
            mem++;
            clk++;
            if(!run) {
                printSPRegs();
                printRam();
            }
            ui->clock->setText("MAR <- PC, PC <- PC + 1");
            return;
        }
        else if(clk==1) {
            MDR = ram[MAR.to_ulong()];
            clk++;
            if(!run) {
                printSPRegs();
                printRam();
            }
            ui->clock->setText("MDR <- Mem[MAR]");
            return;
        }
        else if(clk == 2) {
            IR = MDR;
            clk++;
            if(!run) {
                printRam();
                printSPRegs();
            }
            ui->clock->setText("IR <- MDR");
            return;
        }
        if(operation.at(0)[operation.at(0).size()-1] == ',') {
            for(int i = 0 ; i < operation.length()-1;i++) {
                operation[i] = operation[i+1];
            }
        }
        if(operation.at(0) == "HEX") {
            clk = 0;
            line++;
        }
        else if(operation.at(0) == "DEC") {
            clk = 0;
            line++;
        }
        else if((IR.to_ulong() & 0xF000 )== 0x1000) { //add
            if(clk==3) {
                Neg.reset();
                Zero.reset();
                Pos.reset();
                clk++;
                bitset<3> dest,s1;
                for(int i = 6 ; i <= 8 ; i++) {
                    s1[i-6] = IR[i];
                }
                for(int i = 9 ; i <= 11 ; i++) {
                    dest[i-9] = IR[i];
                }
                if(IR.test(5)) {//Immidiate
                    bitset<5> imm;
                    for(int i = 0 ; i <= 4 ; i++ ) {
                        imm[i] = IR[i];
                    }
                    imm = bitset<5>(myToInt(QString::fromStdString(imm.to_string()),5));
                    this->ALU_Add(dest.to_ulong(),s1.to_ulong(),imm);
                    ui->clock->setText("DR <- R1 + Imm.");
                }
                else {//Register ref.
                    bitset<3> s2;
                    for(int i = 0 ; i <= 2 ; i++ ) {
                        s2[i] = IR[i];
                    }
                    this->ALU_Add(dest.to_ulong(),s1.to_ulong(),s2.to_ulong());
                    ui->clock->setText("DR <- R1 + R2");
                }
                printRegs();
                clk = 0;
                line++;
            }
        }
        else if((IR.to_ulong() & 0xF000 )== 0x5000) {//and
            if(clk==3) {
                Neg.reset();
                Zero.reset();
                Pos.reset();
                clk++;
                bitset<3> dest,s1;
                for(int i = 6 ; i <= 8 ; i++) {
                    s1[i-6] = IR[i];
                }
                for(int i = 9 ; i <= 11 ; i++) {
                    dest[i-9] = IR[i];
                }
                if(IR.test(5)) {//Immidiate
                    bitset<5> imm;
                    for(int i = 0 ; i <= 4 ; i++ ) {
                        imm[i] = IR[i];
                    }
                    imm = bitset<5>(myToInt(QString::fromStdString(imm.to_string()),5));
                    this->ALU_And(dest.to_ulong(),s1.to_ulong(),imm);
                    ui->clock->setText("DR <- R1 & Imm.");
                }
                else {//Register ref.
                    bitset<3> s2;
                    for(int i = 0 ; i <= 2 ; i++ ) {
                        s2[i] = IR[i];
                    }
                    this->ALU_And(dest.to_ulong(),s1.to_ulong(),s2.to_ulong());
                    ui->clock->setText("DR <- R1 & R2");
                }
                if(!run)
                printRegs();
                clk = 0;
                line++;
            }
        }
        else if((IR.to_ulong() & 0xF000 )== 0x9000) {
            if(clk == 3) {
                Neg.reset();
                Zero.reset();
                Pos.reset();
                clk = 0;
                line++;
                bitset<3> dest,s1;
                for(int i = 6 ; i <= 8 ; i++) {
                    s1[i-6] = IR[i];
                }
                for(int i = 9 ; i <= 11 ; i++) {
                    dest[i-9] = IR[i];
                }
                this->ALU_Not(dest.to_ulong(),s1.to_ulong());
                ui->clock->setText("DR <- !SR");
            }

        }
        else if((IR.to_ulong() & 0xF000 )== 0x2000) {//LD
            if(clk == 3) {
                Neg.reset();
                Zero.reset();
                Pos.reset();
                clk++;
                reg tmp(0);
                for(int i = 0 ; i < 9 ; i++) {
                    tmp[i] = IR[i];
                }
                for(int i = 9 ; i < tmp.size() ; i++) {
                    tmp[i] = tmp[i] | IR[8];
                }
                MAR = this->addressAdd(tmp);
                ui->clock->setText("MAR <- PC + offset");
            }
            else if(clk == 4) {
                clk++;
                if(MAR.to_ulong() < 0xFE00) {
                    MDR = ram[MAR.to_ulong()];
                    ui->clock->setText("MDR <- Mem[MAR]");
                }
                else if(MAR.to_ulong() == 0xFE00) {
                    MDR = this->KBDR;
                    ui->clock->setText("MDR <- KBDR");
                }
                else if(MAR.to_ulong() == 0xFE01) {
                    MDR = this->KBSR;
                    ui->clock->setText("MDR <- KBSR");
                }
                else  if(MAR.to_ulong() == 0xFE03) {
                    MDR = this->DSR;
                    ui->clock->setText("MDR <- DSR");
                }
                else{
                    MDR = ram[MAR.to_ulong()];
                    ui->console->setText("runtime Error : Out of range");
                    this->compiled = false;
                    clk = 0;
                }
            }
            else if(clk == 5) {
                clk = 0;
                line++;
                bitset<3> dest;
                for(int i = 9 ; i <= 11 ; i++) {
                    dest[i-9] = IR[i];
                }
                regs[dest.to_ulong()] = MDR;
                if(regs[dest.to_ulong()].test(15)) {
                    this->Neg.set();
                }
                else if(regs[dest.to_ulong()].none()) {
                    this->Zero.set();
                }
                else {
                    this->Pos.set();
                }
                if(!run)
                printRegs();
                ui->clock->setText("DR <- MDR");
            }
        }
        else if((IR.to_ulong() & 0xF000 )== 0xA000) {//LDI
            if(clk == 3) {
                Neg.reset();
                Zero.reset();
                Pos.reset();
                clk++;
                reg tmp(0);
                for(int i = 0 ; i < 9 ; i++) {
                    tmp[i] = IR[i];
                }
                for(int i = 9 ; i < tmp.size() ; i++) {
                    tmp[i] = tmp[i] | IR[8];
                }
                MAR = this->addressAdd(tmp);
                ui->clock->setText("MAR <- PC + offset");
            }
            else if(clk == 4) {
                clk++;
                MDR = ram[MAR.to_ulong()];
                ui->clock->setText("MDR <- Mem[MAR]");
            }
            else if(clk == 5) {
                clk++;
                MAR = MDR;
                ui->clock->setText("MAR <- Mem[PC + offset]");
            }
            else if(clk == 6) {
                clk++;
                if(MAR.to_ulong() < 0xFE00) {
                    MDR = ram[MAR.to_ulong()];
                    ui->clock->setText("MDR <- Mem[Mem[PC + offset]]");
                }
                else if(MAR.to_ulong() == 0xFE00) {
                    MDR = this->KBDR;
                    KBSR.reset(15);
                    ui->clock->setText("MDR <- KBDR");
                }
                else if(MAR.to_ulong() == 0xFE01) {
                    MDR = this->KBSR;
                    ui->clock->setText("MDR <- KBSR");
                }
                else  if(MAR.to_ulong() == 0xFE03) {
                    MDR = this->DSR;
                    ui->clock->setText("MDR <- DSR");
                }
                else {
                    MDR = ram[MAR.to_ulong()];
                    ui->console->setText("runtime Error : Out of range");
                    this->compiled = false;
                    clk = 0;
                }
            }
            else if(clk == 7) {
                clk = 0;
                line++;
                bitset<3> dest;
                for(int i = 9 ; i <= 11 ; i++) {
                    dest[i-9] = IR[i];
                }
                regs[dest.to_ulong()] = MDR;
                if(regs[dest.to_ulong()].test(15)) {
                    this->Neg.set();
                }
                else if(regs[dest.to_ulong()].none()) {
                    this->Zero.set();
                }
                else {
                    this->Pos.set();
                }
                if(!run)
                printRegs();
                ui->clock->setText("DR <- MDR");
            }
        }
        else if((IR.to_ulong() & 0xF000 )== 0x6000) {//LDR
            if(clk == 3) {
                Neg.reset();
                Zero.reset();
                Pos.reset();
                clk++;
                bitset<3> baseR(0);
                bitset<6> imm;
                for(int i = 0 ; i <= 5 ; i++ ) {
                    imm[i] = IR[i];
                }
                for(int i = 6 ; i <= 8 ; i++) {
                    baseR[i-6] = IR[i];
                }
                imm = bitset<6>(myToInt(QString::fromStdString(imm.to_string()),5));
                reg offset = signExtend(imm);
                this->addressAdd(baseR.to_ulong(),offset);
                ui->clock->setText("MAR <- BaseR + offset");
            }
            else if(clk == 4) {
                clk++;
                if(MAR.to_ulong() < 0xFE00) {
                    MDR = ram[MAR.to_ulong()];
                    ui->clock->setText("MDR <- Mem[BaseR + offset]");
                }
                else if(MAR.to_ulong() == 0xFE00) {
                    MDR = this->KBDR;
                    ui->clock->setText("MDR <- KBDR");
                }
                else if(MAR.to_ulong() == 0xFE01) {
                    MDR = this->KBSR;
                    ui->clock->setText("MDR <- KBSR");
                }
                else  if(MAR.to_ulong() == 0xFE03) {
                    MDR = this->DSR;
                    ui->clock->setText("MDR <- DSR");
                }
                else{
                    MDR = ram[MAR.to_ulong()];
                    ui->console->setText("runtime Error : Out of range");
                    this->compiled = false;
                    clk = 0;
                }
            }
            else if(clk == 5) {
                clk = 0;
                line++;
                bitset<3> dest(0);
                for(int i = 9 ; i <= 11 ; i++) {
                    dest[i-9] = IR[i];
                }
                regs[dest.to_ulong()] = MDR;
                if(regs[dest.to_ulong()].test(15)) {
                    this->Neg.set();
                }
                else if(regs[dest.to_ulong()].none()) {
                    this->Zero.set();
                }
                else {
                    this->Pos.set();
                }
                if(!run)
                printRegs();
                ui->clock->setText("DR <- MDR");
            }
        }
        else if((IR.to_ulong() & 0xF000 )== 0xE000) {//LEA
            if(clk == 3) {
                clk++;
                reg tmp(0);
                bitset<3> dest(0);
                for(int i = 9 ; i <= 11 ; i++) {
                    dest[i-9] = IR[i];
                }
                for(int i = 0 ; i < 9 ; i++) {
                    tmp[i] = IR[i];
                }
                for(int i = 9 ; i < tmp.size() ; i++) {
                    tmp[i] = tmp[i] | IR[8];
                }
                regs[dest.to_ulong()] = this->addressAdd(tmp);
                clk = 0;
                line++;
            }
        }
        else if((IR.to_ulong() & 0xF000 )== 0x3000) {//ST
            if(clk == 3) {
                clk++;
                reg tmp(0);
                for(int i = 0 ; i < 9 ; i++) {
                    tmp[i] = IR[i];
                }
                for(int i = 9 ; i < tmp.size() ; i++) {
                    tmp[i] = tmp[i] | IR[8];
                }
                MAR = this->addressAdd(tmp);
                ui->clock->setText("MAR <- PC + offset");
            }
            else if(clk == 4) {
                clk++;
                bitset<3> source(0);
                for(int i = 9 ; i <= 11 ; i++) {
                    source[i-9] = IR[i];
                }
                MDR = regs[source.to_ulong()];
                ui->clock->setText("MDR <- SR");
            }
            else if(clk == 5) {
                clk++;
                if(MAR.to_ulong() < 0xFE00) {
                    ram[MAR.to_ulong()] = MDR;
                    ui->clock->setText("Mem[PC + offset] <- SR" );
                }
                else if(MAR.to_ulong() == 0xFE02) {
                    this->DDR = MDR;
                    ui->clock->setText("I/O(DDR) <- SR");
                }
                else {
                    ui->console->setText("runtime Error : Out of range");
                    this->compiled = false;
                    clk = 0;
                }
                clk = 0;
                line++;

            }
        }
        else if((IR.to_ulong() & 0xF000 )== 0xB000) {//STI
            if(clk == 3) {
                clk++;
                reg tmp(0);
                for(int i = 0 ; i < 9 ; i++) {
                    tmp[i] = IR[i];
                }
                for(int i = 9 ; i < tmp.size() ; i++) {
                    tmp[i] = tmp[i] | IR[8];
                }
                MAR = this->addressAdd(tmp);
                ui->clock->setText("MAR <- PC + offset");
            }
            else if(clk == 4) {
                clk++;
                MDR = ram[MAR.to_ulong()];
                ui->clock->setText("MDR <- Mem[PC + offset]");
            }
            else if(clk == 5) {
                clk++;
                MAR = MDR;
                ui->clock->setText("MAR <- Mem[PC + offset]");
            }
            else if(clk == 6) {
                clk++;
                bitset<3> source(0);
                for(int i = 9 ; i <= 11 ; i++) {
                    source[i-9] = IR[i];
                }
                MDR = regs[source.to_ulong()];
                ui->clock->setText("MDR <- SR");
            }
            else if(clk == 7) {
                clk++;
                if(MAR.to_ulong() < 0xFE00) {
                    ram[MAR.to_ulong()] = MDR;
                    ui->clock->setText("Mem[Mem[Pc + offset]] <- SR");
                }
                else if(MAR.to_ulong() == 0xFE02) {
                    this->DDR = MDR;
                    this->DSR.reset(15);
                    ui->clock->setText("I/O(DDR) <- SR");
                }
                clk = 0;
                line++;
            }
        }
        else if((IR.to_ulong() & 0xF000 )== 0x700) {//STR
            if(clk == 3) {
                clk++;
                reg offset(0);
                bitset<3> baseR(0);
                for(int i = 0 ; i <= 5 ; i++) {
                    offset[i] = IR[i];
                }
                for(int i = 9 ; i < offset.size() ; i++) {
                    offset[i] = offset[i] | IR[5];
                }
                for(int i = 6 ; i < 9 ; i++) {
                    baseR[i-6] = IR[i];
                }
                this->addressAdd(baseR.to_ulong(),offset);
                ui->clock->setText("MAR <- PC + offset");
            }
            else if(clk == 4) {
                clk++;
                bitset<3> source(0);
                for(int i = 9 ; i<= 11 ; i++ ) {
                    source[i-9] = IR[i];
                }
                MDR = regs[source.to_ulong()];
                ui->clock->setText("MDR <- SR");
            }
            else if(clk == 5) {
                clk++;
                ram[MAR.to_ulong()] = MDR;
                ui->clock->setText("Mem[BaseR + Offset] <- SR");
                clk = 0;
                line++;
            }
        }
        else if((IR.to_ulong() & 0xF000 )== 0x0000) {//BR
            if(clk == 3) {
                clk++;
                reg tmp(0);
                for(int i = 0 ; i < 9 ; i++) {
                    tmp[i] = IR[i];
                }
                for(int i = 9 ; i < tmp.size() ; i++) {
                    tmp[i] = tmp[i] | IR[8];
                }
                if((IR[11] & Neg[0]) || (IR[10] & Zero[0]) || (IR[9] & Pos[0]) || (!IR[9] & !IR[10] & !IR[11])) {
                    PC = this->addressAdd(tmp);
                    line = why[PC.to_ulong()];
                    ui->clock->setText("PC <- PC + offset");
                    mem = PC.to_ulong();
                }
                else  {
                    line++;
                }
                clk = 0;
               // ui->clock->setText("PC <- PC");
            }
        }
        else if((IR.to_ulong() & 0xF000 )== 0xC000) {//JMP RET
            if(clk == 3) {
                clk++;
                bitset<3> baseR(0);
                for(int i = 6 ; i < 9 ; i++) {
                    baseR[i-6] = IR[i];
                }
                PC = regs[baseR.to_ulong()];
                clk = 0;
                line = why[PC.to_ulong()];
                mem = PC.to_ulong();
                ui->clock->setText("PC <- SR");
            }
        }
        else if((IR.to_ulong() & 0xF000 )== 0x4000) {//JSR JSRR
            if(clk == 3) {
                if(IR.test(11)) {
                    reg offset(0);
                    for(int i = 0 ; i < 11 ; i++) {
                        offset[i] = IR[i];
                    }
                    for(int i = 11 ; i < offset.size() ; i++) {
                        offset[i] = offset[i] | IR[10];
                    }
                    regs[7] = PC;
                    PC = this->addressAdd(offset);
                    ui->clock->setText("PC <- PC + offset");
                    clk = 0;
                    line = why[PC.to_ulong()];
                    mem = PC.to_ulong();
                }
                else {
                    regs[7] = PC;
                    clk++;
                }
            }
            if(clk == 4) {
                bitset<3> tmp(0);
                for(int i = 6 ; i < 9 ; i++) {
                    tmp[i-6] = IR[i];
                }
                PC = regs[tmp.to_ulong()];
                ui->clock->setText("PC <- SR");
                clk = 0;
                line = why[PC.to_ulong()];
                mem = PC.to_ulong();
            }
        }
        else if(IR.to_ulong()== 0xFFFF) {//HALT
            run = false;
            clk = 0;
            line = 0;
            mem = 0;
            ui->console->setText("Program finished");
            printRegs();
            printSPRegs();
            ui->nxtButton->setEnabled(false);
            ui->runButton->setEnabled(false);
        }
    }
    if(!run) {
        printRegs();
        printSPRegs();
        printRam();
    }
}







void MainWindow::on_gotoButton_clicked()
{
    QString srch = ui->srchle->text();
    if(isNumber(srch))
    {
        bool ok=1;
        int conv_add = srch.toInt(&ok,16);
        QTableWidgetItem * item = ui->RAMtw->item(conv_add,1);
        if(item)
        {
            ui->RAMtw->scrollToItem(item);
        }
        else
        {
            ui->console->setText("wrong address");
        }

    }
    else
    {
        ui->console->setText("wrong address");
    }
}


void MainWindow::on_inputButton_clicked()
{
    if(this->KBSR.test(15)) {
        ui->console->setText("Cpu has not yet read previous data!");
    }
    else {
        QString input = ui->inp_le->text();
        this->KBDR = reg(input.toStdString());
        this->KBSR.set(15);
        this->printSPRegs();
    }
}


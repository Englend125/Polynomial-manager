#include "polinomemenager.h"

polinomemenager::polinomemenager(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(700, 600);

    this->setStyleSheet("QMainWindow {color: #011638}"
        "QWidget {background: #9055A2; color: #011638}"
        "QLabel {background: #E8C1C5; color: #011638}"
        "QPushButton {background: #D499B9; color: #011638}"
        "QTextEdit {background: #D499B9; color: #011638}"
        "QFrame {background: #D499B9; color: #011638}");

    Add = new QPushButton("Add polynomial", this);
    Add->move(50, 50);
    Add->resize(150, 30);
    InPoint = new QPushButton("Polynomial value in point", this);
    InPoint->move(50, 100);
    InPoint->resize(150, 30);
    Plus = new QPushButton("Sum of polynomials", this);
    Plus->move(50, 150);
    Plus->resize(150, 30);
    Multiplicate = new QPushButton("Multiplying polynomials", this);
    Multiplicate->move(50, 200);
    Multiplicate->resize(150, 30);
    Def = new QPushButton("Derivative of a polynomial", this);
    Def->move(50, 250);
    Def->resize(150, 30);
    Del = new QPushButton("Division of polynomials", this);
    Del->move(50, 300);
    Del->resize(150, 30);
    Roots = new QPushButton("Integer roots of a polynomial", this);
    Roots->move(50, 350);
    Roots->resize(150, 30);
    Documentation = new QPushButton("Documentation", this);
    Documentation->move(150, 520);
    Documentation->resize(150, 30);
    IsTheSame = new QPushButton("Polynomials' ==", this);
    IsTheSame->move(50, 400);
    IsTheSame->resize(150, 30);
    Delete = new QPushButton("Delete polynome", this);
    Delete->move(50, 450);
    Delete->resize(150, 30);
    SaveToFile = new QPushButton("Save to file", this);
    SaveToFile->move(490, 520);
    SaveToFile->resize(150, 30);
    LoadFromFile = new QPushButton("Load from file", this);
    LoadFromFile->move(320, 520);
    LoadFromFile->resize(150, 30);

    //rtfd = new QLabel(this);

    data = new QTextEdit(this);
    data->setReadOnly(1);
    data->resize(400, 450);
    data->move(240, 50);
    data->append("Welcome to polynomial manager by Noob_master_2007");

    warning = new QMessageBox(this);

    connect(Add, &QPushButton::clicked, this, &polinomemenager::AddSlot);
    connect(Plus, &QPushButton::clicked, this, &polinomemenager::PlusSlot);
    connect(Multiplicate, &QPushButton::clicked, this, &polinomemenager::MultiplicateSlot);
    connect(Def, &QPushButton::clicked, this, &polinomemenager::DefSlot);
    connect(Roots, &QPushButton::clicked, this, &polinomemenager::RootSlot);
    connect(Documentation, &QPushButton::clicked, this, &polinomemenager::DocumentationSlot);
    connect(SaveToFile, &QPushButton::clicked, this, &polinomemenager::SaveSlot);
    connect(LoadFromFile, &QPushButton::clicked, this, &polinomemenager::LoadSlot);
    connect(IsTheSame, &QPushButton::clicked, this, &polinomemenager::SameSlot);
    connect(InPoint, &QPushButton::clicked, this, &polinomemenager::InPointSlot);
    connect(Delete, &QPushButton::clicked, this, &polinomemenager::DeleteSlot);
    connect(Del, &QPushButton::clicked, this, &polinomemenager::DelSlot);
}

void polinomemenager::ShowWarning(std::string problem) {
    warning->setText(QString::fromStdString(problem));
    warning->show();
}

void polinomemenager::Update() {
    data->clear();
    Bnode* q = base.L;
    int n = 1;
    QString result;

    while (!q->b) {
        result += (QString::fromStdString(std::to_string(n) + ". " 
                   + q->pol.GetStr()) + '\n');
        ++n;
        q = q->next;
    }
    data->setText(result);

    Documentation->setText("Documentation");
    disconnect(Documentation, &QPushButton::clicked, this, &polinomemenager::Update);
    connect(Documentation, &QPushButton::clicked, this, &polinomemenager::DocumentationSlot);
    
}

void polinomemenager::RTFD() {
    error_counter = 0;

    Add->blockSignals(1);
    Plus->blockSignals(1);
    Multiplicate->blockSignals(1);
    InPoint->blockSignals(1);
    Def->blockSignals(1);
    Del->blockSignals(1);
    IsTheSame->blockSignals(1);
    Roots->blockSignals(1);
    LoadFromFile->blockSignals(1);
    SaveToFile->blockSignals(1);
    Delete->blockSignals(1);

    rtfd->resize(300, 400);
    rtfd->show();
}

void polinomemenager::AddSlot() {
    QString s = QInputDialog::getText(this, "Polinome input", "Input polynomial: ");
    std::string new_p = s.toStdString();

    while (!c.Check(new_p)) {
        new_p = c.Get();
        ++error_counter;
    }

    Polinome p(new_p);

    base.push(p);

    Update();
}

void polinomemenager::PlusSlot() {

    int first, second;

    try {
        first = QInputDialog::getInt(this, "First num input", "Input first polynomial number: ");
        if (first > base.size || first <= 0) throw (std::string)"There is no polynomial whith this nummber!";

        second = QInputDialog::getInt(this, "Second num input", "Input second polynomial number: ");
        if (second > base.size || second <= 0) throw (std::string)"There is no polynomial whith this nummber!";
    }
    catch (std::string problem) {
        ++error_counter;
        ShowWarning(problem);
        return;
    }

    Polinome res;
    res = base[first - 1]->pol + base[second - 1]->pol;

    std::string ans = "The result is: ";
    ans += res.GetStr();
    ans += '.';

    int add = QInputDialog::getInt(this, "Result", QString::fromStdString(ans) + "\n If you want to saver this in the base, enter 1, else 0.");

    try {
        if (add == 0) return;
        else if (add == 1) {
            base.push(res);
            Update();
        } else {
            throw (std::string)"Can you read?";
        }
    } catch (std::string problem) {
        ++error_counter;
        ShowWarning(problem);
        return;
    }

}

void polinomemenager::MultiplicateSlot() {

    int first, second;

    try {
        first = QInputDialog::getInt(this, "First num input", "Input first polynomial number: ");
        if (first > base.size || first <= 0) throw (std::string)"There is no polynomial whith this nummber!";

        second = QInputDialog::getInt(this, "Second num input", "Input second polynomial number: ");
        if (second > base.size || second <= 0) throw (std::string)"There is no polynomial whith this nummber!";
    }
    catch (std::string problem) {
        ++error_counter;
        ShowWarning(problem);
        return;
    }

    Polinome res;
    res = base[first - 1]->pol * base[second - 1]->pol;

    std::string ans = "The result is: ";
    ans += res.GetStr();
    ans += '.';

    int add = QInputDialog::getInt(this, "Result", QString::fromStdString(ans) + "\n If you want to saver this in the base, enter 1, else 0.");

    try {
        if (add == 0) return;
        if (add == 1) {
            base.push(res);
            Update();
        }
        else {
            throw (std::string)"Can you read: ";
        }
    }
    catch (std::string problem) {
        ++error_counter;
        ShowWarning(problem);
        return;
    }
}

std::vector<int> GetLetters(Polinome pol) {
    std::vector<int> ans;

    node* q = pol.L;

    while (!q->b) {
        data d;
        d = q->d;

        for (int i = 0; i < 26; ++i) {
            if (d.st[i]) {
                bool f = 1;
                for (int j = 0; j < ans.size(); ++j) {
                    if (ans[j] == i) {
                        f = 0;
                        break;
                    }
                }
                if (f) {
                    ans.push_back(i);
                }
            }
        }

        q = q->next;
    }

    return ans;
}

void polinomemenager::DelSlot() {
    int first, second;

    try {
        first = QInputDialog::getInt(this, "First num input", "Select dividend: ");
        if (first > base.size || first <= 0) throw (std::string)"There is no polynomial whith this nummber!";

        second = QInputDialog::getInt(this, "Second num input", "Select a divisor: ");
        if (second > base.size || second <= 0) throw (std::string)"There is no polynomial whith this nummber!";
        if (base[second - 1]->pol.GetStr() == "0") throw (std::string)"Have you heard anything about mathematics?";

        std::vector<int> ch_1 = GetLetters(base[first - 1]->pol);
        std::vector<int> ch_2 = GetLetters(base[second - 1]->pol);

        if (ch_1.size() > 1 || ch_2.size() > 1) throw (std::string)"There is not one-letter polynomials!";
        if (!(ch_1.empty() || ch_2.empty()) && ch_1[0] != ch_2[0]) throw (std::string)"This polynomials are not same letter!";
    }
    catch (std::string problem) {
        ++error_counter;
        ShowWarning(problem);
        return;
    }

    std::pair<Polinome, Polinome> res;
    res = base[first - 1]->pol / base[second - 1]->pol;

    std::string ans = "The ansver is: ";
    ans += res.first.GetStr();
    ans += " and : ";
    ans += res.second.GetStr();

    int add = QInputDialog::getInt(this, "Result", QString::fromStdString(ans) + "\n \n If you want to add only the result, press 1, \n if only the remainder, press 2, \n if both, press 3, \n else 0.");

    try {
        if (add == 0) return;
        if (add == 1) {
            base.push(res.first);
            Update();
        } else if (add == 2) {
            base.push(res.second);
            Update();
        } else if (add == 3) {
            base.push(res.first);
            base.push(res.second);
            Update();
        } else {
            throw (std::string)"Can you read?";
        }
    }
    catch (std::string problem) {
        ++error_counter;
        ShowWarning(problem);
        return;
    }
}

void polinomemenager::DefSlot() {

    std::string let;
    int n;
    int p;

    try {
        p = QInputDialog::getInt(this, "Polinome num input", "Input polynomial: ");
        if (p <= 0 || p > base.size) {
            throw (std::string)"There is no polynomial whith this nummber!";
        }

        QString let_input = QInputDialog::getText(this, "Varible iput", "Wich varible: ");
        let = let_input.toStdString();

        if (let.size() > 1) throw (std::string)"Variable must be one-letter!";
        if (let.size() == 0) throw (std::string)"Where is a letter";
        if (let[0] < 'a' || let[0] > 'z') throw(std::string)"There is not a letter!";

        n = QInputDialog::getInt(this, "Def num input", "Derivative order: ");

        if (n <= 0) throw (std::string)"The order must be natural!";
    } catch(std::string problem) {
        ShowWarning(problem);
        error_counter++;
        return;
    }

    Polinome res;
    res = base[p - 1]->pol.GetDef(let[0], n);

    std::string ans = "The result is: ";
    ans += res.GetStr();
    ans += '.';

    int add = QInputDialog::getInt(this, "Result", QString::fromStdString(ans) + "\n If you want to saver this in the base, enter 1, else 0.");

    try {
        if (add == 0) return;
        if (add == 1) {
            base.push(res);
            Update();
        }
        else {
            throw (std::string)"Can you read?";
        }
    }
    catch (std::string problem) {
        ++error_counter;
        ShowWarning(problem);
        return;
    }

}

void polinomemenager::RootSlot() {
    int p;
    try {
        p = QInputDialog::getInt(this, "Polinome num input", "Input polynomial: ");
        if (p <= 0 || p > base.size) {
            throw (std::string)"There is no polynomial whith this nummber!";
        }

        if (base[p - 1]->pol.OneVCheck() == 0) {
            return;
        }
    } catch (std::string problem) {
        ShowWarning(problem);
        error_counter++;
        return;
    }

    std::vector<int> res = base[p - 1]->pol.GetRoots();

    std::string ans;

    int n = base[p - 1]->pol.L->d.k;

    if (n == 0) {
        ans = "There are infinity roots!";

        warning->setText(QString::fromStdString(ans));
        warning->show();
        return;
    }

    if (res.size() && !base[p - 1]->pol.L->d.empty()) {
        ans = "The integer roots is: \n";

        for (int i = 0; i < res.size();) {
            for (int j = i; j < 6 && j < res.size(); ++i, ++j) {
                ans += std::to_string(res[j]) + ' ';
            }
            ans += '\n';
        }

        
    } else {
        ans = "There is no integer roots!";
    }

    warning->setText(QString::fromStdString(ans));
    warning->show();
}

void polinomemenager::SameSlot() {
    int first, second;

    try {
        first = QInputDialog::getInt(this, "First num input", "Input first polynomial: ");
        if (first > base.size || first <= 0) throw (std::string)"There is no polynomial whith this nummber!";

        second = QInputDialog::getInt(this, "Second num input", "Input second polynomial: ");
        if (second > base.size || second <= 0) throw (std::string)"There is no polynomial whith this nummber!";
    }
    catch (std::string problem) {
        ++error_counter;
        ShowWarning(problem);
        return;
    }

    bool res = base[first - 1]->pol == base[second - 1]->pol;

    if (res) {
        ShowWarning("Polynomials are same!");
    } else {
        ShowWarning("Polynomials aren't same!");
    }
}

void polinomemenager::InPointSlot() {
    int p;
    try {
        p = QInputDialog::getInt(this, "Polinome num input", "Input polynomial: ");
        if (p <= 0 || p > base.size) {
            throw (std::string)"There is no polynomial whith this nummber!";
        }

    } catch (std::string problem) {
        ShowWarning(problem);
        error_counter++;
        return;
    }

    std::vector<int> let = GetLetters(base[p - 1]->pol);

    std::vector<std::pair<int, int>> data_for(let.size());

    for (int i = 0; i < let.size(); ++i) {
        std::string s = "Input variable value ";
        s += 'a' + let[i];
        int value = QInputDialog::getInt(this, "Polinome num input", QString::fromStdString(s));
        data_for.push_back({let[i], value});
    }

    int ans = base[p - 1]->pol.GetInPoint(data_for);

    ShowWarning("The result is: " + std::to_string(ans));
}

void polinomemenager::DeleteSlot() {
    int p;
    try {
        p = QInputDialog::getInt(this, "Polinome num input", "Input polynomial: ");
        if (p <= 0 || p > base.size) {
            throw (std::string)"There is no polynomial whith this nummber!";
        }

    }
    catch (std::string problem) {
        ShowWarning(problem);
        error_counter++;
        return;
    }
    Bnode* t = base[p - 1];
    base.pop(t);

    Update();
}

//fileslots

void polinomemenager::DocumentationSlot() {
    std::ifstream in("Documentation.txt");

    std::string ans;

    while (!in.eof()) {
        std::string d;
        std::getline(in, d);
        d += '\n';
        ans += d;
    }

    data->clear();

    data->setText(QString::fromStdString(ans));
    in.close();

    Documentation->setText("Back to polynomials");
    disconnect(Documentation, &QPushButton::clicked, this, &polinomemenager::DocumentationSlot);
    connect(Documentation, &QPushButton::clicked, this, &polinomemenager::Update);
}

std::string LastFour(std::string& s) {
    if (s.size() < 4) return "";

    std::string ans;

    for (int i = s.size() - 4; i < s.size(); ++i) {
        ans += s[i];
    }
    return ans;
}

void polinomemenager::SaveSlot() {
    QString s = QInputDialog::getText(this, "File name input", "Input file name:");

    std::string out_name = s.toStdString();

    try {
        if (LastFour(out_name) != ".txt") {
            throw (std::string)"file must be 'txt'!";
        }
        if (out_name == "Documentation.txt" || out_name == "Keks.txt") {
            throw (std::string)"There are program file!";
        }   
    } catch (std::string problem) {
        ShowWarning(problem);
    }

    std::ofstream out(out_name);

    Bnode* q = base.L;

    while (!q->b) {
        out << q->pol.GetStr();
        out << '\n';
        q = q->next;
    }

    out.close();
}

void polinomemenager::LoadSlot() {
    base.clear();

    QString s = QInputDialog::getText(this, "File name input", "Input file name");

    std::string in_name = s.toStdString(); 

    try {
        if (LastFour(in_name) != ".txt") {
            throw (std::string)"file must be 'txt'!";
        }
        if (in_name == "Documentation.txt" || in_name == "Keks.txt") {
            throw (std::string)"This is program file!";
        }
    }
    catch (std::string problem) {
        ShowWarning(problem);
        return;
    }

    std::ifstream in(in_name);

    while (!in.eof()) {
        std::string cur_p;
        std::getline(in, cur_p);
        if (cur_p.empty() || !c.Check(cur_p)) continue;
        Polinome p(cur_p);
        base.push(p);
    }

    in.close();
    Update();
}

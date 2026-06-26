#include <iostream>
#include <vector>
using namespace std;

class NhanVat{
    protected:
        int level;
        int baseAttack;
        int baseDefense;
        int damage;
        int HP;
        int maxHP;

        bool gotHit = false;
        bool stunEffect = false;
        bool poisonEffect = false;
        bool slowEffect = false;
        bool weakEffect = false;
        bool lostMindEffect = false;

        string typeChar;
    public:
        virtual void Nhap()
        {
            cout<<"Nhap level cua nhan vat: ";
            cin>>level;
        }

        virtual void Xuat()
        {
            cout<<"Level: "<<level<<endl;
            cout<<"Base Attack: "<<baseAttack<<endl;
            cout<<"Base Defense: "<<baseDefense<<endl;
            cout<<"Damage: "<<damage<<endl;
            cout<<"Max HP: "<<maxHP<<endl;
            cout<<"HP: "<<HP<<endl;
        }

        string getLoaiNV()
        {
            return typeChar;
        }

        bool getHit()
        {
            gotHit = true;
            return gotHit;
        }

        string getTypeChar()
        {
            return typeChar;
        }

        void BossCalc()
        {
            baseAttack *= 2.5;
            baseDefense *= 2.5;
            damage *= 2.5;
            maxHP *= 2.5;
        }

        bool IsDead()
        {
            if (HP <= 0)
            {
                return true;
            }
            return false;
        }

        void Defend()
        {
            if (gotHit)
            {
                baseDefense = baseDefense * 1.25;
                gotHit = false;
            }
            else
                HP += maxHP * 0.1;
        }

        void Attack(NhanVat *nv)
        {
            int Attack = randInt(0.8 * baseAttack, 1.1 * baseAttack);
            int Defense = randInt(0.8 * nv->baseDefense, 1.1 * nv->baseDefense);

            if (Attack > Defense)
            {
                nv->HP -= Attack;
            }
        }
};

class Tanker: public NhanVat{
    public:
        Tanker(int level, string typeChar)
        {
            switch(level)
            {
                case 1:
                    baseAttack = 50;
                    baseDefense = 50;
                    damage = 5;
                    maxHP = 80;
                    break;
                case 2:
                    baseAttack = 55;
                    baseDefense = 70;
                    damage = 8;
                    maxHP = 100;
                    break;
                case 3:
                    baseAttack = 60;
                    baseDefense = 90;
                    damage = 12;
                    maxHP = 120;
                    break;
                case 4:
                    baseAttack = 65;
                    baseDefense = 110;
                    damage = 17;
                    maxHP = 140;
                    break;
                case 5:
                    baseAttack = 70;
                    baseDefense = 130;
                    damage = 22;
                    maxHP = 160;
                    break;
                default:
                    cout<<"Cap do cua nhan vat khong hop le!";
                    break;
            }

            if (typeChar == "Boss")
            {
                BossCalc();
            }
            
            HP = maxHP;
            this->level = level;
        }
        void Nhap()
        {
            NhanVat::Nhap();
        }
        void Xuat()
        {
            NhanVat::Xuat();
        }
};

int NhapLevel()
{
    int level;
    cout<<"Nhap level cua nhan vat: ";
    cin>>level;
    return level;
}

float randFloat()
{
    float r;
    return r;
}

int randInt(int from, int to)
{
    int random; // random trong khoang tu from toi to
    return random;
}

int main()
{
    cout<<"Nhap thong tin tran danh! "<<endl;
    int n;
    cout<<"Nhap so luong nhan vat nguoi choi: ";
    cin>>n;

    if (n > 5)
    {
        cout<<"So luong nguoi choi khong hop le!";
        return 0;
    }

    int level;

    vector<NhanVat*> playerList;
    vector<NhanVat*> boss;

    cout<<"Nhap thong tin nguoi choi: "<<endl;
    for (int i = 0; i < n; i++)
    {
        int choice;
        cout<<"Chon loai nhan vat (1. Tanker, 2. Fighter, 3. Ranger): ";
        cin>>choice;
        NhanVat* nv;
        switch(choice)
        {
            case 1:
                level = NhapLevel();
                nv = new Tanker(level, "Tanker");
                playerList.push_back(nv);
                break;
            default:
                cout<<"Nhap thong tin khong hop le!";
                break;
        }
    }
    
    cout<<"Nhap thong tin boss: "<<endl;

    int choice;
    cout<<"Chon loai nhan vat (1. Tanker, 2. Fighter, 3. Ranger): ";
    cin>>choice;
    NhanVat* nv;
        switch(choice)
        {
            case 1:
                level = NhapLevel();
                nv = new Tanker(level, "Boss");
                boss.push_back(nv);
                break;
            default:
                cout<<"Nhap thong tin khong hop le!";
                break;
        }

    /*cout<<"Thong tin cac nhan vat co trong tran danh: "<<endl;

    for (int i = 0; i < n; i++)
    {
        cout<<"Thong tin nguoi choi thu: "<<i+1<<endl;
        playerList[i]->Xuat();
    }

    cout<<"Thong tin boss: "<<endl;
        boss[0]->Xuat();
    }*/

    cout<<"Bat dau tran danh!"<<endl;

    while (playerList.size() != 0 || boss[0]->IsDead() == false)
    {
        cout<<"Luot di cua nguoi choi: "<<endl;
        for (int i = 0; i < playerList.size(); i++)
        {
            cout<<"Luot di nhan vat thu "<<i+1<<endl;
            cout<<"Ban chon tan cong hay phong thu? (0. Tan cong, 1. Phong thu): ";
            cin>>choice;
            switch(choice)
            {
                case 0:
                    playerList[i]->Attack(boss[0]);
                    boss[0]->getHit();
                    break;
                case 1:
                    playerList[i]->Defend();
                    break;
            }
        }

        cout<<"Luot di cua boss: "<<endl;
        float r = randFloat(); // Trong khoang tu 0.0 toi 1.0
        if (r < 0.7)
        {
            float target = randFloat();
            int index;
            if (target < 0.5)
            {
                for (int i = 0; i < playerList.size(); i++)
                {
                    if (playerList[i]->getTypeChar() == "Tanker")
                    {
                        index = i;
                    }
                }
            }
            else if (target < 0.5 + 0.3)
            {
                for (int i = 0; i < playerList.size(); i++)
                {
                    if (playerList[i]->getTypeChar() == "Fighter")
                    {
                        index = i;
                    }
                }
            }
            else
            {
                for (int i = 0; i < playerList.size(); i++)
                {
                    if (playerList[i]->getTypeChar() == "Ranger")
                    {
                        index = i;
                    }
                }
            }
            boss[0]->Attack(playerList[index]);
            if (playerList[index]->IsDead())
            {
                playerList.erase(playerList.begin() + index);
            }
        }
        else
        {
            boss[0]->Defend();
        }
    }

    return 0;
}

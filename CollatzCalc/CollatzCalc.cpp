#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <set> // 이진 트리 적용!
#include <vector>
#include "BigInteger.h"
#include "BigIntegerLibrary.h"

using namespace std;

// set<BigInteger>* Hailstones => 콜라츠 추측이 성립하는 수의 집합
// under => x가 콜라츠의 추측을 만족시키면 x <= k가 참이 되게 하는 k의 최댓값
bool isHailstone(BigInteger num, set<BigInteger>* Hailstones, BigInteger under)
{
    BigInteger num_roop = num;
    vector<BigInteger> tHailstones; // 중간 계산과정에서 나타난 수들을 임시로 저장 

    while (num_roop != 1)
    {
        if (num_roop <= under) // under 이하의 수에 대해선 증명됨
            break;
        set<BigInteger>::iterator iter = Hailstones->find(num_roop); // 집합에서 수가 있는지 찾아본다
        if (iter != Hailstones->end()) // 수가 존재하면
            break; // 루프를 탈출한다. 더 계산할 필요도 없이 성립함

        tHailstones.push_back(num_roop); // 저장

        if (num_roop % 2 == 0) // if n is even
            num_roop /= 2; // n / 2
        else // if n is odd
            num_roop = BigInteger(3) * num_roop + 1; // 3n + 1

        if (num_roop == num) // 자기자신으로 돌아오면 순환루프이므로
            return false; // 반례
    }

    int len = tHailstones.size();
    for (uint32_t i = 0; i < len; i++)
        Hailstones->insert(tHailstones[i]); // 임시로 저장해뒀던 수들을 저장

    return true; // 성립
}

int main()
{
    set<BigInteger> Hailstones;
    BigInteger verified = 0;

    // 반복 한번에 i가 1씩 증가하고 i가 100000보다 커지면 반복이 종료됨.
    for (BigInteger i = 1;; i++)
    {
        if (!isHailstone(i, &Hailstones, verified))
        {
            cout << "The counterexample : " << i << endl;
            system("PAUSE");
        }
        verified++;
        Hailstones.erase(i);
    }
    system("PAUSE");
}
/**
 * Author: dayte timofeyu finalku
 * Description: Алгоритм Куна: максимальное паросочетание в двудольном графе.
 * Input: leftPart[v] --- соседи $v$ в правой доле, нумерация с 0; заполнить match числом $-1$, вызвать kuhn(). Результат: power --- размер паросочетания, match[u] --- пара вершины $u$ правой доли.
 * Time: O(VE)
 */
const int MAXN = 300;

int lastTimeUsed[MAXN * MAXN];
int match[MAXN * MAXN];
vector<int> leftPart[MAXN * MAXN];

int timer = 1;
int n, m;
bool dfs(int v) {
    if (lastTimeUsed[v] == timer)
        return false;
    lastTimeUsed[v] = timer;
    for (auto e : leftPart[v]) {
        if (match[e] == -1 || dfs(match[e])) {
            match[e] = v;
            return true;
        }
    }
    return false;
}

int power = 0;
void kuhn() {
    // можно i < n
    for (int i = 0; i < MAXN; i++) {
        power += dfs(i);
        timer++;
    }
}

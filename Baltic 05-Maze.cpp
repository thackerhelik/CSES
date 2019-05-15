/*
Making input to graph is a hard part.
Then we can solve with BFS since edges are unweighted.
Answer is min(BFS(start with black edge), BFS(start with white edge))
*/

/*
When you walk through a storm
Hold your head up high
And don't be afraid of the dark
At the end of the storm
There's a golden sky
And the sweet silver song
of the lark
Walk on, through the wind
Walk on, through the rain
Though your dreams be tossed
and blown
Walk on, walk on
With hope in your heart
And you'll never walk alone
YNWA
*/

//hell_hacker
//IT TAKES EVERYTHING and IT IS NOT LUCK
//PICK ME LAST -- COME OUT OF N^WHERE
//WHY NOT?

/*
And you came my way on a winner's day
Shouted loudly come out and play
Can't you tell I got news for you
Sun is shining and so are you
*/

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>

using namespace __gnu_pbds;
using namespace std;

#define endl '\n'
#define fo(i,n) for(i=0;i<n;++i)
#define forr(i,n) for(i=n-1;i>=0;--i)
#define rep(i,a,b) for(i=a;i<=b;++i)
#define per(i,a,b) for(i=b;i>=a;--i)

#define ffs(a) __builtin_ffs(a) // find first set
#define clz(a) __builtin_clz(a) // count leading zeroes
#define ctz(a) __builtin_ctz(a) // count trailing zeroes
#define popc(a) __builtin_popcount(a) // count set bits
#define popcll(a) __builtin_popcountll(a) //count set bits for long long int

#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define yolo "debug_statement"

typedef long long int ll;
typedef long double ld;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

const ll inf = 1e9;
const ld eps = 1e-9;
const ld pi=acos(-1);
const ll mod=1000000007;

ll powmod(ll a,ll b,ll mo=mod){ll res=1;a%=mo; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mo;a=a*a%mo;}return res;}

inline ll inv_(ll a) {return powmod(a, mod-2, mod);}
inline ll add(ll a, ll b){a%=mod; b%=mod; a+=b;if(a>=mod)a-=mod;return a;}
inline ll mul(ll a, ll b){a%=mod; b%=mod; return a*1ll*b%mod;}
inline ll sub(ll a, ll b){a%=mod; b%=mod; a-=b;if(a<0)a+=mod;return a;}

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

/*USAGE
ordered_set X;
X.insert(1);
X.insert(3);
cout << *X.find_by_order(1) << endl; //3
cout << X.order_of_key(-5) << endl; //0
cout << X.order_of_key(1) << endl; //0
cout << (end(X) == X.order_of_key(100)) << endl; //true since utne elements nahi hai
*/

#if DEBUG && !ONLINE_JUDGE

    #define debug(args...)     (Debugger()) , args

    class Debugger
    {
        public:
        Debugger(const std::string& _separator = ", ") :
        first(true), separator(_separator){}

        template<typename ObjectType>
        Debugger& operator , (const ObjectType& v)
        {
            if(!first)
                std::cerr << separator;
            std::cerr << v;
            first = false;
            return *this;
        }
        ~Debugger() {  std::cerr << endl;}

        private:
        bool first;
        std::string separator;
    };

    template <typename T1, typename T2>
    inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p)
    {
        return os << "(" << p.first << ", " << p.second << ")";
    }

    template <typename T1, unsigned long int N>
    inline std::ostream& operator << (std::ostream& os, const std::array<T1, N>& a){
        bool first = true;
        os << "[";
        for(unsigned int i = 0; i < N; i++)
        {
            if(!first)
                os << ", ";
            os << a[i];
            first = false;
        }
        return os << "]";   
    }

    template<typename T>
    inline std::ostream &operator << (std::ostream & os,const std::vector<T>& v)
    {
        bool first = true;
        os << "[";
        for(unsigned int i = 0; i < v.size(); i++)
        {
            if(!first)
                os << ", ";
            os << v[i];
            first = false;
        }
        return os << "]";
    }

    template<typename T>
    inline std::ostream &operator << (std::ostream & os,const std::set<T>& v)
    {
        bool first = true;
        os << "[";
        for (typename std::set<T>::const_iterator iii = v.begin(); iii != v.end(); ++iii)
        {
            if(!first)
                os << ", ";
            os << *iii;
            first = false;
        }
        return os << "]";
    }

    template<typename T1, typename T2>
    inline std::ostream &operator << (std::ostream & os,const std::map<T1, T2>& v)
    {
        bool first = true;
        os << "[";
        for (typename std::map<T1, T2>::const_iterator iii = v.begin(); iii != v.end(); ++iii)
        {
            if(!first)
                os << ", ";
            os << *iii ;
            first = false;
        }
        return os << "]";
    }

#else
    #define debug(args...)                  // Just strip off all debug tokens
#endif

const int INF = 1000000000;
vector<vector<pair<int, int>>> adj;
int w, h, X1, X2, Y1, Y2;
string str;
bool used[505*505][2];
int ans;

void bfs(int colour){
	queue<tuple<int, int, int>>q;
	q.push({X1*(w + 1) + Y1, 0, colour});
	used[X1*(w + 1) + Y1][colour] = true;
	while(!q.empty()){
		int frm = get<0>(q.front());
		int dist = get<1>(q.front());
		int color = get<2>(q.front());
		q.pop();
		if(frm == (X2*(w + 1) + Y2)){
			ans = dist;
			break;
		}
		for(int i = 0; i < sz(adj[frm]); ++i){
			pair<int,int> it = adj[frm][i];
			if(!used[it.fi][it.se] && it.se != color){
				q.push({it.fi, dist + 1, it.se});
				used[it.fi][it.se] = true;
			}
		}
	}
}

 int main(){
    #if ONLINE_JUDGE
        ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
	#endif

    cin >> w >> h;

	adj.resize((w+5)*(h+5));

	cin >> Y1 >> X1 >> Y2 >> X2;

	for(int i = 0; i < 2*h + 1; ++i){
		cin >> str;
		if(i & 1){
			//diagonal
			for(int j = 0; j < sz(str); ++j){
				if(!(j & 1)){
					int frm = (i/2)*(w + 1) + j/2, to = ((i + 1)/2)*(w + 1) + j/2;
					if(str[j] == 'b'){
						adj[frm].push_back({to, 0});
						adj[to].push_back({frm, 0});
					}
					else if(str[j] == 'w'){
						adj[frm].push_back({to, 1});
						adj[to].push_back({frm, 1});
					}	
				}
				else{
					int frm = ((i + 1)/2)*(w + 1) + j/2, to = (i/2)*(w + 1) + j/2 + 1;
					if(str[j] == 'b'){
						adj[frm].push_back({to, 0});
						adj[to].push_back({frm, 0});
					}
					else if(str[j] == 'w'){
						adj[frm].push_back({to, 1});
						adj[to].push_back({frm, 1});
					}
				}
			}
		}
		else{
			//horizontal
			for(int j = 0; j < sz(str); ++j){
				int frm = (i/2)*(w + 1) + j, to = (i/2)*(w + 1) + j + 1;
				if(str[j] == 'b'){
					adj[frm].push_back({to, 0});
					adj[to].push_back({frm, 0});
				}
				else if(str[j] == 'w'){
					adj[frm].push_back({to, 1});
					adj[to].push_back({frm, 1});
				}
			}
		}
	}

	ans = 100000000;
	memset(used, false, sizeof(used));
	bfs(0);
	int finalans = ans;
	ans = 100000000;
	memset(used, false, sizeof(used));
	bfs(1);
	finalans = min(finalans, ans);
	cout << finalans << endl;

    //#if !ONLINE_JUDGE
    //    cout << fixed << setprecision(12) << "-------------------------------------------------\n";
    //    cout << double(clock())/CLOCKS_PER_SEC << " seconds" << endl;
    //#endif
    return 0;
}


// 時間複雜度：O(V^2E)
struct Flow{
	struct Edge{
		int v, rc, rid;
	};
	vector<vector<Edge>> G;
	void add(int u, int v, int c){
		G[u].push_back({v, c, G[v].size()});
		G[v].push_back({u, 0, G[u].size()-1});
	}
	vector<int> dis, it;

	Flow(int n){
		G.resize(n);
		dis.resize(n);
		it.resize(n);
	}

	int dfs(int u, int t, int f){
		if (u==t || f==0) return f;
		for (int &i=it[u] ; i<G[u].size() ; i++){
			auto &[v, rc, rid] = G[u][i];
			if (dis[v]!=dis[u]+1) continue;
			int df = dfs(v, t, min(f, rc));
			if (df<=0) continue;
			rc -= df;
			G[v][rid].rc += df;
			return df;
		}
		return 0;
	}

	int flow(int s, int t){
		int ans = 0;
		while (true){
			fill(dis.begin(), dis.end(), INF);
			queue<int> q;
			q.push(s);
			dis[s] = 0;

			while (q.size()){
				int u = q.front(); q.pop();
				for (auto [v, rc, rid] : G[u]){
					if (rc<=0 || dis[v]<INF) continue;
					dis[v] = dis[u]+1;
					q.push(v);
				}
			}
			if (dis[t]==INF) break;

			fill(it.begin(), it.end(), 0);
			while (true){
				int df = dfs(s, t, INF);
				if (df<=0) break;
				ans += df;
			}
		}
		return ans;
	}
};
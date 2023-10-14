#define _CXX_DEBUG
#include <bits/stdc++.h>

using namespace std;

const int TIME_MAX = 1024 * 1024;
int current_time = 1;

const int PMAX = 1e5 + 7;
struct _proj {
    string name;
    int id;
    int days, best_before, score;
    vector<pair<string, int>> named_skills;
    vector<pair<int, int>> skills;

    _proj() {}
};
vector<_proj> projects;
map<string, int> proj_id;

const int CMAX = 1e5 + 7;
struct worker {
    string name;
    int id;
    vector<pair<string, int>> named_skills;
    vector<pair<int, int>> skills;
};
vector<worker> workers;
vector<worker> to_add[TIME_MAX + 1];
vector<double> worker_bias;
map<string, int> work_id;

const int SMAX = 800;
vector<double> skill_weight;
map<string, int> skill_id;

double eval_worker(worker w) {
    double ans = -worker_bias[w.id];
    for(auto s : w.skills) {
        ans += skill_weight[s.first] * (1. * s.second * s.second);
    }

    return ans;
}

double eval_project(_proj p) {
    if(current_time + p.days <= p.best_before) { // Before deadline
        double price = (1. * p.score) / (1. * p.days * p.skills.size());
        double urgency = (1. * current_time + p.days) / (1. * p.best_before);
        return urgency * price;
    }
    else { // After deadline
        double price = max(-100., (1. * p.score - (current_time + p.days) - p.best_before) / (1. * p.days * p.skills.size()));
        return price;
    }
}

template < typename T >
void key_sort(vector<T> &vec, double (*key)(T)) {
    /* vector<int> keys(vec.size());

    iota(keys.begin(), keys.end(), 0);
    sort(keys.begin(), keys.end(), [=](int a, int b) { return key(a) < key(b); });

    vector<T> ret = vec;
    for(int i = 0; i < ret.size(); i++) {
        ret[i] = vec[keys[i]];
    }
    vec = ret; */

    sort(vec.begin(), vec.end(), [=](auto a, auto b) { return key(a) < key(b); });
}

bool can_take(_proj p) {
    vector<pair<int, int>> skills_cpy = p.skills;
    for(auto &w : workers) {
        bool taken = false;
        for(auto s : w.skills) {
            for(int i = 0; i < skills_cpy.size(); i++) {
                if(skills_cpy[i].first == s.first && skills_cpy[i].second <= s.second) {
                    skills_cpy.erase(skills_cpy.begin() + i);
                    taken = true;
                    break;
                }
            }
            if(taken == true) break;
        }
    }
    return (skills_cpy.size() == 0);
}

int main()
{
    int C, P; cin >> C >> P;

    workers.resize(C);
    for(auto &w : workers) {
        cin >> w.name;

        int nr_skills; cin >> nr_skills;
        w.named_skills.resize(nr_skills);
        for(auto &s : w.named_skills) {
            cin >> s.first >> s.second;
        }
    }

    projects.resize(P);
    for(auto &p : projects) {
        cin >> p.name;
        cin >> p.days >> p.score >> p.best_before;
        p.best_before += 1; // Shift all by 1

        int nr_skills; cin >> nr_skills;
        p.named_skills.resize(nr_skills);
        for(auto &s : p.named_skills) {
            cin >> s.first >> s.second;
        }
    }

    {
        int _id = 0;
        for(auto &w : workers) {
            work_id[w.name] = _id++;
            w.id = _id - 1;
        }
    }

    {
        int _id = 0;
        for(auto &p : projects) {
            proj_id[p.name] = _id++;
            p.id = _id - 1;
        }
    }

    {
        int _id = 0;
        for(auto &w : workers) {
            for(auto &s : w.named_skills) {
                if(skill_id.find(s.first) == skill_id.end())
                    skill_id[s.first] = _id++;
                w.skills.push_back({skill_id[s.first], s.second});
            }
            w.named_skills.clear();
        }
        for(auto &p : projects) {
            for(auto &s : p.named_skills) {
                if(skill_id.find(s.first) == skill_id.end())
                    skill_id[s.first] = _id++;
                p.skills.push_back({skill_id[s.first], s.second});
            }
            p.named_skills.clear();
        }
    }

    skill_weight.resize(skill_id.size(), 1);
    worker_bias.resize(skill_id.size(), 0);


    int64_t sub_score = 0;

    map<int, int> shown;

    while(current_time <= TIME_MAX) {
        if(shown[current_time / 1024] == 0) {
            cerr << "Reached time " << current_time << " with sub_score " << sub_score << endl;
            shown[current_time / 1024] = 1;
        }

        key_sort(projects, eval_project);
        reverse(projects.begin(), projects.end());

        for(auto w : to_add[current_time])
            workers.push_back(w);
        to_add[current_time].clear();
        key_sort(workers, eval_worker);

        // for(auto w : workers) cerr << "AA " << current_time << w.name << " " << w.skills[0].first << " " << w.skills[0].second << endl;

        vector<_proj> new_projects;
        for(auto p : projects) {
            vector<worker> taken_workers;
            vector<worker> other_workers;
            vector<pair<int, int>> skills_cpy = p.skills;
            vector<int> mentored(skills_cpy.size(), 0);
            vector<worker> chosen(skills_cpy.size());
						vector<bool> used(workers.size(), 0);
            for(int iter=0;iter<workers.size();++iter) {
								if(used[iter]) continue;
								auto w=workers[iter];	
                bool taken = false;
                int to_add = 0;
                auto cpy_w = w;
                for(auto &s : w.skills) {
                    pair<int, int> done;
                    for(int i = 0; i < skills_cpy.size(); i++) {
                        if(skills_cpy[i].first == s.first && skills_cpy[i].second - mentored[i] <= s.second) {
                            if(skills_cpy[i].second >= s.second) s.second += 1;
                            done = skills_cpy[i];
                            mentored.erase(mentored.begin() + i);
                            skills_cpy.erase(skills_cpy.begin() + i);
                            taken = true;
														used[iter]=true;
                            break;
                        }
                    }
                    if(taken == true) {
												used[iter]=true;
                        for(auto other_s : cpy_w.skills) {
                            for(int i = 0; i < skills_cpy.size(); i++) {
                                if(skills_cpy[i].second <= other_s.second && skills_cpy[i].first == other_s.first) {
																		if(mentored[i]==0) iter=0;
                                    mentored[i] = 1;
                                }
                            }
                        }
                        for(int i = 0; i < p.skills.size(); i++) {
                            if(p.skills[i] == done && chosen[i].name == "") {
                                chosen[i] = w;
                                break;
                            }
                        }
                        break;
                    }
                }

                if(!taken) {
                    other_workers.push_back(w);
                }
                else {
										used[iter]=true;
                    taken_workers.push_back(w);
                }
            }

						key_sort(other_workers, eval_worker);
						other_workers.resize(unique(other_workers.begin(), other_workers.end())-other_workers.begin());

            if(skills_cpy.size() == 0) {
                workers = other_workers;
                for(auto w : taken_workers)
                    to_add[current_time + p.days].push_back(w);

                // cerr << current_time << " " << p.name << " " << eval_project(p) << endl;

                cout << p.name << endl;
                for(auto w : chosen)
                    cout << w.name << " ";
                cout << endl;

                if(p.days + current_time <= p.best_before) sub_score += p.score;
                else sub_score += max(0, p.score - (p.days + current_time - p.best_before));
            }
            else {
                new_projects.push_back(p);
            }
        }

        projects = new_projects;
        if(new_projects.size() == projects.size()) {
            while(to_add[current_time + 1].size() == 0) current_time++;
        }

        current_time += 1;
    }

    cerr << "Final " << sub_score << endl;

    return 0;
}

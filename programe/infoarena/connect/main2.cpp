#include <stdio.h>
#include <iostream>
#include <bitset>

// using uint32_t = unsigned int;
// using uint64_t = unsigned long long;

const uint32_t low16 = 0x0000ffff;
const uint32_t hig16 = 0xffff0000;

FILE *in = fopen("connect.in", "r"), *out = fopen("connect.out", "w");
inline void rd(int& _r) {
    fscanf(in, "%d", &_r);
}

const int NMAX = 5e4 + 7, MMAX = 2e5 + 7;
uint32_t edge[MMAX];

// DSU
uint32_t size_father[NMAX];
uint32_t nrcomp = 0;

// UNDO
uint64_t undo_stack[MMAX];
uint32_t undo_stack_size = 0;

inline uint32_t get_size_father(uint32_t node) {
    std::cerr << node << " " << (size_father[node] & low16) << std::endl;
    while(node != (size_father[node] & low16))
        node = size_father[node] & low16;
    return size_father[node];
}

inline void dsu_update(uint32_t edge) {
    std::cerr << std::bitset<32>(edge) << std::endl;

    uint32_t szft_x = get_size_father(edge >> 16);
    uint32_t szft_y = get_size_father(edge & low16);
    std::cerr << std::bitset<32>(szft_x) << std::endl;
    std::cerr << std::bitset<32>(szft_y) << std::endl;

    uint32_t xored_fathers = (szft_x ^ szft_y) & low16;
    undo_stack[undo_stack_size++] = ((uint64_t)(szft_x) << 32) | szft_y;

    if(__builtin_expect(xored_fathers != 0, true)) {
        if(szft_x < szft_y) {
            uint32_t swap = szft_x;
            szft_x = szft_y; szft_y = swap;
        }

        size_father[szft_x & low16] += (szft_y & hig16);
        size_father[szft_y & low16] ^= xored_fathers;

        nrcomp -= 1;
    }
}

inline void dsu_undo() {
    uint32_t szft_x = undo_stack[--undo_stack_size] >> 32;
    uint32_t szft_y = undo_stack[undo_stack_size];

    if(__builtin_expect(szft_x != szft_y, true)) {
        size_father[szft_x & low16] = szft_x;
        size_father[szft_y & low16] = szft_y;

        nrcomp += 1;
    }
}

// QUEUE
uint32_t q_updates[MMAX], q_updates_tmp[MMAX];
uint32_t update_count = 0, reversed_count = 0;

inline void q_update(uint32_t edge_index) {
    q_updates[update_count++] += (edge_index << 1) | 0;
    dsu_update(edge[edge_index]);
}

inline void q_undo() {
    if(reversed_count == 0) {
        for(int i = 0; i < update_count; i++) dsu_undo();
        for(int i = 0; i < update_count / 2; i++) {
            uint32_t swap = q_updates[i];
            q_updates[i] = q_updates[update_count - 1 - i] | 1;
            q_updates[update_count - 1 - i] = swap | 1;
        }
        for(int i = 0; i < update_count; i++) dsu_update(edge[q_updates[i] >> 1]);

        reversed_count = update_count;
    }

    uint32_t pushable = 0;
    while(!(q_updates[--update_count] & 1)) {
        q_updates_tmp[pushable++] = q_updates[update_count];
        dsu_undo();
    }


    uint32_t pushed_past = reversed_count & (-reversed_count);
    // copy from q_updates[update_count - pushed_past] to q_updates[update_count - pushed_past + pushable]

    std::cerr << "Pushable " << pushable << std::endl;
    std::cerr << "Pushed Past " << pushed_past << std::endl;
    std::cerr << "Update Count " << update_count << std::endl;

    for(int i = pushed_past - 1; i >= 0; i--) {
        std::cerr << "Cpy " << update_count - pushed_past + i << " to " << update_count - pushed_past + pushable + i << std::endl;
        q_updates[update_count - pushed_past + pushable + i] = q_updates[update_count - pushed_past + i];
    }
    while(pushable) {
        q_updates[update_count++ - pushed_past] = q_updates_tmp[--pushable];
    }

    update_count--; reversed_count--;
    dsu_undo();
}

int main() {
    int n, m; rd(n); rd(m); nrcomp = n;
    for(int i = 0; i < m; i++) {
        int x, y; rd(x); rd(y);
        edge[i] = (x << 16) | y;
    }
    for(int i = 1; i <= n; i++) {
        size_father[i] = (1 << 16) + i;
    }

    uint64_t sol = 0;
    for(uint32_t left = 0, right = -1; left < m; left++) {
        std::cerr << "LR" << left << " " << right << std::endl;
        while(nrcomp > 1 && right < m) {
            std::cerr << "NA" << nrcomp << " " << right << std::endl;
            q_update(++right);
            std::cerr << "NB" << nrcomp << " " << right << std::endl;
        }
        std::cerr << left << " " << right << std::endl;
        if(nrcomp == 1) sol += m - right + 1;
        q_undo();
    }

    fprintf(out, "%llu", sol);
}
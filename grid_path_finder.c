#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct treenode { int x; int y; struct treenode* par;double dist;double travdis; char vis;} node;//σημεια για καθε πιθανη γωνια που υπαρχει στον χάρτι
// par = γονιώς της γωνίας
//dist = ευθεία απόσταση απο τον στόχο
//travdis = απόσταση που έχει διανύσει
//vis = 1 αν το έχουμε ελεγξει


//συνάρτηση που ελέγχει αν το μονοπάτι αναμεσα απο δυο σημεια είναι κενο
int clear(node a, node b, int **r) {    // επιστρεφει 1 αν περναει απο κάτω, 2 αν περναει απο πάνω
    int fl = 0;
    if (a.y>b.y) {
        for (int i = a.y - 1;i>=b.y; i--) {
            if (r[a.x][i] == 1) {
                fl = 1;
            }
        }
    } else {
        for (int i = a.y + 1;i<=b.y; i++) {
            if (r[a.x][i] == 1) {
                fl = 1;
            }
        }
    }
    if (a.x>b.x) {
        for (int i = a.x - 1;i>b.x; i--) {
            if (r[i][b.y] == 1) {
                fl = 1;
            }
        }
    } else {
        for (int i = a.x + 1;i<b.x; i++) {
            if (r[i][b.y] == 1) {
                fl = 1;
            }
        }
    }
    if (fl == 0) return 1;

    if (a.x>b.x) {
        for (int i = a.x - 1;i>=b.x; i--) {
            if (r[i][a.y] == 1) {
                return 0;
            }
        }
    } else {
        for (int i = a.x + 1;i<=b.x; i++) {
            if (r[i][a.y] == 1) {
                return 0;
            }
        }
    }
    if (a.y>b.y) {
        for (int i = a.y - 1;i>b.y; i--) {
            if (r[b.x][i] == 1) {
                return 0;
            }
        }
    } else {
        for (int i = a.y + 1;i<b.y; i++) {
            if (r[b.x][i] == 1) {
                return 0;
            }
        }
    }
    return 2;

}

//ευθύγραμμη απόσταση αναμεσα απο δυο σημεια
double getdis(node a, node b) {
    double gdis = (b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y);
    return sqrt(gdis);
}


//δέχεται ενα σημείο και επιστρέφει τον δείκτη για εναν πινακα με ολα τα σημεία στα οποια το μονοπάτι ειναι κενο. Επιπλεον αλλαζει τη τιμη του δεικτη για τον πινακα
node* pospathar(node a, int c, node *corners, int **r, int *pp) {
    int te = 0;
    for (int i = 0;i<c;i++) {
        if (clear(a, corners[i], r)) {
            te++;
        }
    }
    node *pos = malloc(te*sizeof(node));
    *pp = te;
    int tete = 0;
    for (int i = 0;i<c;i++) {
        if (clear(a, corners[i], r)) {
            pos[tete++] = corners[i];
        }
    }
    return pos;

}



node zoom;  //θεση σκουπας
node here;  //θεση στο μονοπάτι
node targ;  //θεση στοχου

int main() {
    int dim;  //διαβαζει διασταση δωματίου, θεση σκουπας και στόχου
    int used;  //για να μπορει να μεταγλωτιστη το προγραμμα
    used = scanf("%d", &dim);
    if (dim < 0 || dim > 10000) return 1;
    int z_x;
    int z_y;
    used = scanf("%d %d", &z_x, &z_y);
    if ((z_x < 0 || z_x > dim) || (z_y < 0 || z_y > dim)) return 1;
    int t_x;
    int t_y;
    used = scanf("%d %d", &t_x, &t_y);
    if ((t_x < 0 || t_x > dim) || (t_y < 0 || t_y > dim)) return 1;

    //φτιαχνει πινακα για το δωματιο και το διαβαζει
    int **r = malloc(dim * sizeof(int*));
    for (int i = 0; i< dim;i++) {
        r[i] = malloc(dim * sizeof(int));
    }

    for (int i=dim -1; i>=0; i--) {
        for (int j = dim -1; j>=0;j--) {
            used = scanf("%1d", &r[j][i]);
        }
    }
    if (r[z_x][z_y] == 1 || r[t_x][t_y] == 1) return 1;
    used++;

    //ελεγχεται ολος χαρτης και αποθηκεύονται εδω όλα τα σημεία που είναι γωνίες, δηλαδη διαγωνια εχουν εμποδιο και πανω και αριστερα ή πανω και δεξια ή κατω και δεξια ή κατω και αριστερα κενό
    node *all = malloc((dim*dim/2)*sizeof(node));
    int c = 0;
    //ελεγχος για τις ακρες του πινακ για να μην βγει εκτος οριων του πινακα
    for (int i =1;i<dim-1;i++) {
        if (r[0][i] && !r[1][i]) {
            if (!r[0][i-1] && !r[1][i-1]) {
                all[c].y = i-1;
                all[c].x = 1;
                c++;
            }
            if (!r[0][i+1] && !r[1][i+1]) {
                all[c].y = i+1;
                all[c].x = 1;
                c++;
            }
        }
        if (r[i][dim - 1] && !r[i][dim - 2]) {
            if (!r[i-1][dim -1] && !r[i-1][dim - 2]) {
                all[c].y = dim - 2;
                all[c].x = i - 1;
                c++;
            }
            if (!r[i+1][dim - 1] && !r[i+1][dim -2]) {
                all[c].y = dim - 2;
                all[c].x = i + 1;
                c++;
            }
        }
        if (r[dim - 1][i] && !r[dim -2][i]){
            if (!r[dim - 1][i-1] && !r[dim -2][i-1]) {
                all[c].y = i - 1;
                all[c].x = dim -2;
                c++;
            }
            if (!r[dim - 1][i+1] && !r[dim - 2][i+1]){
                all[c].y = i + 1;
                all[c].x = dim -2;
                c++;
            }
        }
        if (r[i][0] && !r[i][1]) {
            if (!r[i-1][0] && !r[i-1][1]){
                all[c].y = 1;
                all[c].x = i - 1;
                c++;
            }
            if (!r[i+1][0] && !r[i+1][1]){
                all[c].y = 1;
                all[c].x = i + 1;
                c++;
            }
        }
    }
    //ελεγχος για τον υπολοιπο πίνακα
    for (int i = 1; i< dim-1;i++) {
        for (int j = 1;j<dim-1;j++) {
            if (r[i][j] && !r[i-1][j]) {
                if (!r[i][j-1] && !r[i-1][j-1]) {
                    all[c].y = j-1;
                    all[c].x = i-1;
                    c++;
                }
                if (!r[i][j+1] && !r[i-1][j+1]){
                    all[c].y = j + 1;
                    all[c].x = i - 1;
                    c++;
                }
            }
            if (r[i][j] && !r[i+1][j]) {
                if (!r[i][j-1] && !r[i+1][j-1]) {
                    all[c].y = j - 1;
                    all[c].x = i + 1;
                    c++;
                }
                if (!r[i][j+1] && !r[i+1][j+1]){
                    all[c].y = j + 1;
                    all[c].x = i + 1;
                    c++;
                }
            }
        }
    }
    //με τον παραπανω τροπο υπάρχουν πιθανος καποια σημεια που μετρουνται πανω απο μια φορα γιαυτο δημιουργειται νεος πινακας με μια φορα καθε σημείο
    int doub = 0;
    for (int i = 0;i<c;i++) {
        for (int j = i+1;j<c;j++) {
            if (all[i].x == all[j].x && all[i].y == all[j].y && all[j].x != 999999) {
                all[j].x = 999999;
                doub++;
            }
        }
    }
    int tempc = 0;
    c = c -doub;
    node *corners = malloc((c+1)*sizeof(node));  // c + 1 επειδη στη συνεχεια προσθετει και τον στοχο στα σημεια
    int i = 0;
    //νεος πινακας με τα σωστα σημεια
    while (i<c) {
        if (all[tempc].x != 999999) {
            corners[i].x = all[tempc].x;
            corners[i].y = all[tempc].y;
            corners[i].dist = getdis(corners[i], zoom);  //αρχικοποιήση τιμών 
            corners[i].travdis = dim*dim*dim;  //κατι απιθανα μεγάλο
            corners[i].vis = 0;
            //r[corners[i].x][corners[i].y] = 7;
            i++;
        }
        tempc++;
    }
    zoom.x = z_x;  //αρχικοποιήση τιμών
    zoom.y = z_y;
    zoom.travdis = 0;
    //printf("target is %d %d\n", t_x, t_y);
    targ.x = t_x;
    targ.y = t_y;
    zoom.dist = getdis(zoom, targ);
    zoom.travdis = 0;
    

    // for (int i = 0;i<c;i++){
    //     corners[i].dist = getdis(corners[i], zoom);

    // }

    //προσθηκη του στόχου
    corners[c].x = targ.x;  
    corners[c].y = targ.y;
    corners[c].dist = dim*dim*dim;
    corners[c].travdis = dim*dim*dim;
    c++;

    //ενας πινακας (με ιδιοτητες ουραας) που θα ελεγχει τις πιιθανες διαδρομας απο καθε πιθανό σημείο. καθε σημειο μπαινει εδω το πολυ μια φορα (μεσο του vis)
    node *checklist = malloc(c*sizeof(node));
    checklist[0] = zoom;  //ξεκιναει απο το σημειο της σκοθπας
    int checkcount = 1;  //το τελος της οθρας
    int front = 0;  //η αρχη της
    while (checkcount-1>=front) {  //οσο δεν ειναι κενη
        int poscounter = 0;
        node *neigh = pospathar(checklist[front], c, corners, r, &poscounter);  //πινακς με το σημεια που συνδεονται με το σημειο που βρισκομαστε
        for (int i = 0;i<poscounter;i++) {
            //για καθε σημειο που υπαρχει μονοπατι ελεγχεται αν η προηγούμενη αποσταση που είχα διανύσει είναι μικρότερη απο την απόσταση που χρειάζεται το τρέχων σημειο(δηλαδή το σημείο του checklist) να φτάσει σε αυτό
            if (checklist[front].travdis + getdis(neigh[i], checklist[front]) < neigh[i].travdis) {  
                neigh[i].travdis = checklist[front].travdis + getdis(neigh[i], checklist[front]);  // αν είναι μικρότερη η διαδρομη τοτε αντικαθιστα την προηγουμενη τιμη 
                neigh[i].dist = neigh[i].travdis + getdis(neigh[i], targ);
                neigh[i].par = &checklist[front];  //επιπλεον το τρεχων σημειο γινεται γονεας του σημειου που ελεγχεται
                if (neigh[i].vis == 0 && !(neigh[i].x == targ.x && neigh[i].y == targ.y)) {  // αν το σημειο δεν εχει μπει στο checklist και δεν είναι ο στοχος, μπαινει
                    checklist[checkcount] = neigh[i];
                    checkcount++;
                    neigh[i].vis = 1;
                }
            }
            for (int j =0;j<c;j++) {  //ανανεονοτναι οι τιμες του βασικου πινακα με τις καινουργιες
                if (neigh[i].x == corners[j].x && neigh[i].y == corners[j].y) {
                    corners[j].travdis = neigh[i].travdis;
                    corners[j].dist = neigh[i].dist;
                    corners[j].par = neigh[i].par;
                    corners[j].vis = neigh[i].vis;
                }
            }
        }
        front++;
        //ταξινομουνται τα σημεια του checklist ωστε να ελεγχθουν πρώτα τα πιθανως πιο γρήγορα
        for (int i = front;i<checkcount;i++) {
            int min = i;
            for (int j = i+1;j<checkcount;j++) {
                if (checklist[j].dist< checklist[min].dist) {
                    min = j;
                }
            }
            node tempno = checklist[i];
            checklist[i] = checklist[min];
            checklist[min] = tempno;
        }
        free(neigh);

    }
    //αν ο στοχος δεν εχει γονεα σημαίνει οτι κανενα μονοπάτι απο το σκοθπα δεν μπορεί να φτασει σε αυτον αρα ειναι αδυνατη η λυση
    if (!corners[c-1].par) {
        printf("0\n");
        return 0;
    }

    // αφου υπαρχει μονοπάτι ξεκινόντας απο τη σκούπα καταγράφονται οι κινησεις του μονοπατιου σε νεο πίνακα
    char *mov = malloc(dim*dim*(sizeof(char)));
    int movcount = 0;
    here = corners[c-1];
    while (here.x != zoom.x || here.y != zoom.y) {
        r[here.x][here.y] = 2;
        int ri = clear(here, *here.par, r);
        if (ri == 2 && here.x > here.par->x) {
            for (int i = here.par->x;i<here.x;i++) {
                mov[movcount++] = 76; //left
                r[i][here.y] = 2;
                //printf("that left %d %d\n", i, here.y);
                
            }
        } else if (ri == 2) {
            for (int i = here.x;i<here.par->x;i++) {
                mov[movcount++] = 82;//righ
                r[i][here.y] = 2;
                //printf("that right %d %d\n", i, here.y);
            }
        }
        if (ri == 2 && here.y > here.par->y) {
            for (int i = here.par->y;i<here.y;i++) {
                mov[movcount++] = 85; //up
                r[here.par->x][i] = 2;
                //printf("that up %d %d\n", here.par->x, i);
            }
        } else if (ri == 2) {
            for (int i = here.y;i<=here.par->y;i++) {
                mov[movcount++] = 68; // down
                r[here.par->x][i] = 2;
                //printf("that down %d %d\n", here.par->x, i);
            }
        }
        if (ri == 1 && here.y > here.par->y) {
            for (int i = here.par->y;i<here.y;i++) {
                mov[movcount++] = 85;
                r[here.x][i] = 2;
                //printf("this up %d %d\n", here.x, i);
            }
        } else if (ri == 1) {
            for (int i = here.y;i<=here.par->y;i++) {
                mov[movcount++] = 68;
                r[here.x][i] = 2;
                //printf("this down %d %d\n", here.x, i);
            }
        }
        if (ri == 1 && here.x > here.par->x) {
            for (int i = here.par->x;i<here.x;i++) {
                mov[movcount++] = 76;
                r[i][here.par->y] = 2;
                //printf("this left %d %d\n", i, here.par->y);
            }
        } else if (ri == 1) {
            for (int i = here.x;i<here.par->x;i++) {
                mov[movcount++] = 82;
                r[i][here.par->y] = 2;
                //printf("this right %d %d\n", i, here.par->y);
            }
        }
        here = *here.par;
    }
    //τελος εμφανιζονται αναποδα ωστε να ξεκινάε απο την σκουπα
    for (int i = movcount-1;i>=0;i--) {
        printf("%c", mov[i]);
    }
    printf("\n");
    for (int i=dim -1; i>=0; i--) {
        for (int j = dim -1; j>=0;j--) {
            //printf("%d ", r[j][i]);
            if (j == z_x && i == z_y) {
                printf("3 ");
            } else if (j == t_x && i == t_y) {
                printf("3 ");
            } else {
                printf("%d ", r[j][i]);
            }
        }
        printf("\n");
    }


    for (int i = 0; i< dim;i++)
      free(r[i]);
    free(r);
    free(all);
    free(corners);
    free(checklist);
    free(mov);
    return 0;
}

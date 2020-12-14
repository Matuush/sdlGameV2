const GRASS = 3;
const WATER = 1;
const DIRT = 2;
const BLANK = 0;
const MIN_WATER = 0.2;
module.exports = function mapGenerator(input) {
    /**
     * @type {Array<Array<Number>>}
     */
    var rv = [];
    const seed = new Seed(input);
    //INIT
    for (var i = 0; i < 15; i++) {
        rv[i] = [];
        for (var j = 0; j < 15; j++) {
            rv[i][j] = BLANK;
        }
    }

    //SET ALL DIRT
    for (var i = 0; i < rv.length; i++) {
        for (var j = 0; j < rv[i].length; j++) {
            rv[i][j] = DIRT;
        }
    }
    //DECIDE POSSIBILITY
    // var r = Math.floor(seed.rnd() * 3);
    var r = 0
    switch (r) {
        //Lake
        case 0:
            {
                let lakeMid = randomFiled(rv, seed);
                let targerWaterCount = Math.round(rv.length * rv[0].length * MIN_WATER);
                let targerRadius = Math.round(Math.sqrt(targerWaterCount / Math.PI));
                rv[lakeMid[0]][lakeMid[1]] = WATER;
                let x = lakeMid[0];
                let y = lakeMid[1] + 1;
                let count = 0;
                let markedForDeletion = [];
                while (x < rv.length && y < rv[0].length && x > 0 && y > 0 && count < 4 * targerRadius * targerRadius) {
                    rv[x][y] = WATER;
                    if (seed.rnd() < 0.3 || !hasWaterNeighbour(rv, x, y, markedForDeletion)) {
                        markedForDeletion.push([x, y]);
                    }
                    try {
                        if (
                            (isWater(rv, x, y - 1) && !isWater(rv, x + 1, y))//IS ABOVE AND NOT TO RIGHT - GO RIGHT
                        ) {
                            x++;
                        } else
                            if (
                                (isWater(rv, x - 1, y) && !isWater(rv, x, y - 1)) //IS TO LEFT AND NOT ABOVE - GO UP
                            ) {
                                y--;
                            } else
                                if (
                                    (isWater(rv, x, y + 1) && !isWater(rv, x - 1, y)) //IS BELOW AND NOT TO LEFT - GO LEFT
                                ) {
                                    x--;
                                } else
                                    if (
                                        (isWater(rv, x + 1, y) && !isWater(rv, x, y + 1))//IS TO RIGHT AND NOT BELOW - GO DOWN
                                    ) {
                                        y++;
                                    }
                    } catch (e) {
                        break;
                    }
                    count++;

                }
                console.log(markedForDeletion);
            }
            break;
        // 1 River
        case 1:
            break;
        // 2 Rivers
        case 2:
        default:

    }

    //SET WATER
    while (calculateWaterLevel(rv) < MIN_WATER) {

        break;
    }
    return rv;
}
class Seed {
    constructor(seed) {
        this.seed = seed;
    }
    /**
     * @returns {Number}
     */
    rnd() {
        return Math.random();
    }
    /**
     * @returns {String}
     */
    toString() {
        return this.seed;
    }
}
/**
 * 
 * @param {Array<Array<Number>>} map
 * @returns {Number} 
 */
function calculateWaterLevel(map) {
    var t = 0;
    var w = 0;
    for (var i = 0; i < map.length; i++) {
        for (var j = 0; j < map[i].length; j++) {
            t++;
            if (map[i][j] == WATER) w++;
        }
    }
    return w / t;
}
/**
 * 
 * @param {Array<Array<Number>>} map 
 * @param {Seed} seed 
 * @returns {Array<Number>}
 */
function randomFiled(map, seed) {
    var rv = [];
    rv[0] = Math.round(seed.rnd() * (map.length - 1));
    rv[1] = Math.round(seed.rnd() * (map[0].length - 1));
    return rv;
}
/**
 * 
 * @param {Array<Array<Number>>} map 
 * @param {Number} x 
 * @param {Number} y 
 * @returns {Boolean}
 */
function isWater(map, x, y) {
    return map[x][y] == WATER;
}
/**
 * 
 * @param {Array<Array<Number>>} map 
 * @param {Number} x 
 * @param {Number} y 
 * @param {Array<Array<Number>>} mfd
 * @returns {Boolean}
 */
function hasWaterNeighbour(map, x, y, mfd) {
    var rv = false;
    try {
        rv = rv || map[x + 1][y] == WATER
    } catch (e) {}
    try {
        rv = rv || map[x][y + 1] == WATER
    } catch (e) {}
    try {
        rv = rv || map[x][y - 1] == WATER
    } catch (e) {}
    try {
        rv = rv || map[x - 1][y] == WATER
    } catch (e) {}
    return  rv;
}   
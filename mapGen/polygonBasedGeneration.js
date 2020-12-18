const GRASS = 3;
const WATER = 1;
const DIRT = 2;
const BLANK = 0;
const LAKE_ROUNDNES = 3;
const seedrandom = require('seedrandom');
const md5 = require('md5');
/**
 * @param {String} seedString
 * @returns {GameMap}
 */
module.exports = function Generate(seedString) {
    var seed = new Seed(md5(seedString));
    var map = new GameMap(15, 15, DIRT);
    map.addRandomLake(10, 15, seed);
    return map;
}
// 2D
class Region {
    /**
     * 
     * @param {Region | null} parentRegion Parent region of this region
     */
    constructor(parentRegion = null) {
        this.parent = parentRegion;
    }
}
class Polygon extends Region {
    /**
     * 
     * @param {Regio | null} parentRegion 
     * @param {Array<Point>} points
     */
    constructor(parentRegion, points) {
        super(parentRegion);
        this.vertices = points;
        /**
         * @type {Array<Segment>}
         */
        this.edges = [];
        for (var i = 0; i < this.vertices.length; i++) {
            var iBefore = i - 1 >= 0 ? i - 1 : this.vertices.length - 1;
            this.edges.push(new Segment(this.parent, this.vertices[i], this.vertices[iBefore]))
        }
    }
    /**
     * 
     * @param {Point} point 
     * @returns {Boolean} 
     */
    isInside(point) {
        var collisions = 0;
        const { x, y } = point;
        for (var edge of this.edges) {
            var yMin = Math.min(edge.a.y, edge.b.y);
            var yMax = Math.max(edge.a.y, edge.b.y);
            var xInt = edge.getXfromY(y);
            if (x < xInt) continue;
            if (y < yMin || y > yMax) continue;
            collisions++;
        }
        return collisions % 2 === 1;
    }
}
class GameMap extends Region {
    /**
     * 
     * @param {Number} width max X
     * @param {Number} height max Y
     */
    constructor(width, height, defaultBlock) {
        super();
        this.w = width;
        this.h = height;
        this.defaultBlock = defaultBlock;
        /**
         * @type {Array<Polygon>}
         */
        this.lakes = [];
    }
    /**
     * @returns {Array<Array<Number>>}
     */
    toPixels() {
        /**
         * @type {Array<Array<Number>>}
         */
        var rv = [];
        // Default block
        for (var i = 0; i < this.w; i++) {
            rv[i] = [];
            for (var j = 0; j < this.h; j++) {
                rv[i][j] = this.defaultBlock;
            }
        }
        // Lakes
        for (var lake of this.lakes) {
            for (var i = 0; i < rv.length; i++) {
                for (var j = 0; j < rv[0].length; j++) {
                    if (
                        (lake.isInside(new Point(this, i + 0.5, j + 0.5)))
                    ) {
                        rv[i][j] = WATER;
                    }
                }
            }
        }
        return rv;
    }
    /**
     * 
     * @param {Number} targetArea 
     * @param {Number} vertices Number of vertices
     * @param {Seed} seed
     * @returns {Void}
     */
    addRandomLake(targetArea, vertices, seed) {
        var r = Math.sqrt(targetArea / Math.PI);
        var p = this.randomPoint(seed);
        /**
         * @type {Array<Number>}
         */
        var magnitudes = [r];
        for (var i = 1; i < vertices; i++) {
            magnitudes[i] = magnitudes[i - 1] + r * Math.pow(((seed.random() - 0.5) * 2), LAKE_ROUNDNES);
        }
        var points = magnitudes.map((v, i) => Point.polarTransalte(p, Math.PI * 2 / vertices * i, v));
        this.lakes.push(new Polygon(this, points))
    }
    /**
     * @param {Seed} seed
     * @returns {Point}
     */
    randomPoint(seed) {
        return new Point(this, this.w * seed.random(), this.h * seed.random());
    }
    /**
     * @returns {Array<DrawInstruction>} 
     */
    getInsts() {
        /**
         * @type {Array<DrawInstruction>}
         */
        var rv = [];
        for (var lake of this.lakes) {
            for (var edge of lake.edges) {
                rv.push(new LineInstruction(edge.a, edge.b));
            }
            for (var vertex of lake.vertices) {
                rv.push(new PointInstruction(vertex));
            }
        }
        return rv;
    }
}
class DrawInstruction {
    /**
     * 
     * @param {String} type
     */
    constructor(type) {
        this.type = type;
    }
}
class LineInstruction extends DrawInstruction {
    /**
     * 
     * @param {Point} a 
     * @param {Point} b 
     */
    constructor(a, b) {
        super("line");
        this.a = {
            x: new Number(a.x),
            y: new Number(a.y)
        }
        this.b = {
            x: new Number(b.x),
            y: new Number(b.y)
        }
    }
}
class PointInstruction extends DrawInstruction {
    /**
     * 
     * @param {Point} point 
     */
    constructor(point) {
        super("point");
        this.x = new Number(point.x);
        this.y = new Number(point.y);
    }
}
// 1D
class Curve {
    /**
     * 
     * @param {Region} parentRegion The region this curve is associated with
     */
    constructor(parentRegion) {
        if (!parentRegion) throw new Error("Curve must have a parent region.");
    }
}
class Segment extends Curve {
    constructor(parentRegion, point1, point2) {
        super(parentRegion);
        if (!point1 || !point2) throw new Error("Segment must have two points.");
        this.a = point1;
        this.b = point2;
    }
    /**
     * @param {Number} y
     * @returns {Number | undefined}
     */
    getXfromY(y) {
        var yMax = Math.max(this.a.y, this.b.y);
        var yMin = Math.min(this.a.y, this.b.y);
        var xMax = Math.max(this.a.x, this.b.x);
        var xMin = Math.min(this.a.x, this.b.x);
        if (y < yMin || y > yMax) return;
        var r = (y - yMin) / (yMax - yMin);
        return xMin + (xMax - xMin) * r;
    }
    /**
     * @param {Number} x
     * @returns {Number}
     */
    getYfromX(x) {
        var yMax = Math.max(this.a.y, this.b.y);
        var yMin = Math.min(this.a.y, this.b.y);
        var xMax = Math.max(this.a.x, this.b.x);
        var xMin = Math.min(this.a.x, this.b.x);
        if (x < xMin || x > xMax) return;
        var r = (x - xMin) / (xMax - xMin);
        return yMin + (yMax - yMin) * r;
    }
}
// POINT
class Point {
    /**
     * 
     * @param {Region} parentRegion The region this point is associated with
     * @param {Number} x The X coordinate
     * @param {Number} y The Y coordinate
     */
    constructor(parentRegion, x, y) {
        if (!parentRegion) throw new Error("Point must have a parent region.");
        if (x === undefined || x === null) throw new Error("Point must have y coordinate.");
        if (y === undefined || y === null) throw new Error("Point must have x coordinate.");
        this.parent = parentRegion;
        this.x = x;
        this.y = y;
    }
    /**
     * 
     * @param {Point} point 
     * @param {Number} angle Angle in radians
     * @param {Number} magnitude Magnitude of the translation
     * @returns {Point} 
     */
    static polarTransalte(point, angle, magnitude) {
        var x = Math.round((point.x + Math.cos(angle) * magnitude) * 1e3) / 1e3;
        var y = Math.round((point.y - Math.sin(angle) * magnitude) * 1e3) / 1e3;
        return new Point(point.parent, x, y);
    }
}

// SEED
class Seed extends String {
    /**
     * 
     * @param {String} seed The string seed
     */
    constructor(seed) {
        super(seed);
        /**
         * @returns {Number}
         */
        this.random = new seedrandom(this);
        for (var i = 0; i < 100; i++) {
            this.random();
        }
    }
}
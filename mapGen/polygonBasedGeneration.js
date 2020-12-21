const GRASS = 3;
const WATER = 1;
const DIRT = 2;
const BLANK = 0;
const LAKE_ROUNDNES = 2;
const LAKE_DIVIATION = 1 / 2;
const MAX_RIVER_SEGMENT_LENGTH = 1;
const RIVER_MAX_DEVIATION = 1.3;
const seedrandom = require('seedrandom');
const md5 = require('md5');
/**
 * @param {String} seedString
 * @returns {GameMap}
 */
module.exports = function Generate(seedString) {
    var seed = new Seed(md5(seedString));
    var map = new GameMap(15, 15, DIRT);
    var type = seed.random();
    if (type < 0.5) {
        map.addRandomLake(10, 6, seed);
    } else {
        map.addRandomRiver(1, seed);
    }

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
class Rectangle extends Region {
    /**
     * 
     * @param {Point} point1 
     * @param {Point} point2 
     * @param {Point} point3 
     * @param {Point | null} point4
     */
    constructor(point1, point2, point3, point4 = null) {
        if (!(point1.parent === point2.parent && point1.parent === point3.parent)) throw new Error("Rectangle points must have the same parent.");
        super(point1.parent);
        this.a = point1;
        this.b = point2;
        this.c = point3;
        this.d = point4 ? point4 : new Point(this.parent, this.a.x + this.c.x - this.b.x, this.a.y + this.b.y - this.c.y);
        this.vertices = [this.a, this.b, this.c, this.d];
        this.edges = this.vertices.map((v, i) => {
            if (i == 0) {
                i = this.vertices.length;
            }
            return new Segment(this.parent, v, this.vertices[i - 1]);
        });
        this.middle = new Line(this.parent, this.a, this.c).getIntersect(new Line(this.parent, this.d, this.b));
    }
    /**
     * 
     * @param {Point} point 
     * @returns {Boolean} 
     */
    isInside(point) {
        for (var edge of this.edges) {
            if (edge.intersects(new Segment(this.parent, this.middle, point))) return false;
        }
        return true;
    }
}
class Polygon extends Region {
    /**
     * 
     * @param {Region | null} parentRegion 
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
        /**
         * @type {Array<River>}
         */
        this.rivers = [];
        this.middle = new Point(this, this.w / 2, this.h / 2);
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
        // Rivers 
        for (var river of this.rivers) {
            for (var i = 0; i < rv.length; i++) {
                for (var j = 0; j < rv[0].length; j++) {
                    if (
                        (river.isInside(new Point(this, i + 0.5, j + 0.5)))
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
            magnitudes[i] = magnitudes[i - 1] + LAKE_DIVIATION * r * Math.pow(((seed.random() - 0.5) * 2), LAKE_ROUNDNES);
        }
        var points = magnitudes.map((v, i) => Point.polarTransalte(p, Math.PI * 2 / vertices * i, v));
        this.lakes.push(new Polygon(this, points));
    }
    /**
     * 
     * @param {Number} width 
     * @param {Seed} seed
     */
    addRandomRiver(width, seed) {
        if (seed.random() < 0.5) {
            var x = seed.random() * this.w;
            if (seed.random() < 0.5) {
                var y = 0;
            } else {
                var y = this.h
            }
        } else {
            var y = seed.random() * this.h;
            if (seed.random() < 0.5) {
                var x = 0;
            } else {
                var x = this.w
            }
        }
        var points = [new Point(this, x, y)];
        while (Point.distance(points[points.length - 1], this.middle) > MAX_RIVER_SEGMENT_LENGTH) {
            var a = points[points.length - 1];
            var b = this.middle;
            var s = new Segment(this, a, b);
            var nextX = a.x + Math.sign(b.x - a.x) * (MAX_RIVER_SEGMENT_LENGTH * Math.SQRT1_2);
            var nextY = s.getYfromX(nextX);
            nextX += RIVER_MAX_DEVIATION * 2 * (seed.random() - 0.5);
            nextY += RIVER_MAX_DEVIATION * 2 * (seed.random() - 0.5);
            points.push(new Point(this, nextX, nextY));
        }
        points.push(this.middle)
        this.rivers.push(new River(new Path(this, points), width));
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
        for (var river of this.rivers) {
            for (var segment of river.path.segments) {
                rv.push(new LineInstruction(segment.a, segment.b));
                if (!segment.lastHitbox) {
                    console.log("No last hitbox.");
                    continue;
                }
                for (var edge of segment.lastHitbox.edges) {
                    rv.push(new LineInstruction(edge.a, edge.b));
                }
            }
        }
        return rv;
    }
}
// DRAW INSTRUCTIONS
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
        this.parent = parentRegion;
    }
    /**
     * 
     * @param {Point} point 
     * @param {Number} radius 
     * @returns {Boolean}
     */
    isWithin(point, radius) {
        throw new Error("Can not call isWithin on unspecified curve.");
    }
}
class Path extends Curve {
    /**
     * 
     * @param {Region} parentRegion 
     * @param {Array<Point>} points 
     */
    constructor(parentRegion, points) {
        super(parentRegion);
        this.points = points;
        /**
         * @type {Array<Segment>}
         */
        this.segments = [];
        for (var i = 1; i < points.length; i++) {
            this.segments.push(new Segment(this.parent, points[i - 1], points[i]));
        }
    }
    /**
     * 
     * @param {Point} point 
     * @param {Number} radius 
     */
    isWithin(point, radius) {
        for (var s of this.segments) {
            if (s.isWithin(point, radius)) return true;
        }
        return false;
    }
}
class River {
    /**
     * 
     * @param {Path} path 
     * @param {Number} width 
     */
    constructor(path, width) {
        this.path = path;
        this.width = width;
    }
    /**
     * 
     * @param {Point} point 
     * @returns {Boolean}
     */
    isInside(point) {
        return this.path.isWithin(point, this.width);
    }
}
class Segment extends Curve {
    /**
     * 
     * @param {Region} parentRegion 
     * @param {Point} point1 
     * @param {Point} point2 
     */
    constructor(parentRegion, point1, point2) {
        super(parentRegion);
        if (!point1 || !point2) throw new Error("Segment must have two points.");
        this.a = [point1, point2].find(v => v.x == Math.min(point1.x, point2.x));
        this.b = [point1, point2].find(v => v.x == Math.max(point1.x, point2.x));
        this.length = Math.pow(Math.pow(this.a.x - this.b.x, 2) + Math.pow(this.a.y - this.b.y, 2), 1 / 2);
        this.angle = Math.acos(Math.abs(this.a.x - this.b.x) / this.length);
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
    /**
     * 
     * @param {Point} point 
     * @param {Number} radius 
     * @returns {Boolean}
     */
    isWithin(point, radius) {
        if (this.a.distance(point) < radius || this.b.distance(point) < radius) return true;
        var deltaX = Math.round(Math.sin(Math.PI / 2 - Math.atan((this.b.x - this.a.x) / (this.a.y - this.b.y))) * radius * 1e3) / 1e3
        var deltaY = Math.round(Math.cos(Math.PI / 2 - Math.atan((this.b.x - this.a.x) / (this.a.y - this.b.y))) * radius * 1e3) / 1e3;
        var a = new Point(this.parent, this.a.x + deltaX, this.a.y + deltaY);
        var b = new Point(this.parent, this.a.x - deltaX, this.a.y - deltaY);
        var c = new Point(this.parent, this.b.x - deltaX, this.b.y - deltaY);
        var d = new Point(this.parent, this.b.x + deltaX, this.b.y + deltaY);
        if (new Line(this.parent, a, b).isOn(c)) {
            a = new Point(this.parent, this.a.x + deltaX, this.a.y - deltaY);
            b = new Point(this.parent, this.a.x - deltaX, this.a.y + deltaY);
            c = new Point(this.parent, this.b.x - deltaX, this.b.y + deltaY);
            d = new Point(this.parent, this.b.x + deltaX, this.b.y - deltaY);
        }
        this.lastHitbox = new Rectangle(a, b, c, d);
        return this.lastHitbox.isInside(point);
    }
    /**
     * 
     * @param {Segment} segment 
     * @returns {Boolean}
     */
    intersects(segment) {
        var l1 = new Line(this.parent, this.a, this.b);
        var l2 = new Line(segment.parent, segment.a, segment.b);
        if (!l1.intersects(l2)) return false;
        if (l1.matches(l2)) return l1.isOn(l2.a) || l1.isOn(l2.b) || l2.isOn(l1.a) || l2.isOn(l1.b);
        var intersect = l1.getIntersect(l2);
        return l1.isOn(intersect) && l2.isOn(intersect);
    }
    /**
     * 
     * @param {Point} point 
     * @return {Boolean}
     */
    isOn(point) {
        return this.getYfromX(point.x) === point.y;
    }

}
class Line extends Curve {
    /**
     *  
     * @param {Region} parentRegion
     * @param {Point} point1 
     * @param {Point} point2 
     */
    constructor(parentRegion, point1, point2) {
        super(parentRegion);
        if (!point1 || !point2) throw new Error("Line must have two points.");
        this.a = [point1, point2].find(v => v.x == Math.min(point1.x, point2.x));
        this.b = [point1, point2].find(v => v.x == Math.max(point1.x, point2.x));
    }
    /**
     * 
     * @param {Number} x 
     * @returns {Number} y
     */
    getYfromX(x) {
        var yMax = Math.max(this.a.y, this.b.y);
        var yMin = Math.min(this.a.y, this.b.y);
        var xMax = Math.max(this.a.x, this.b.x);
        var xMin = Math.min(this.a.x, this.b.x);
        var r = (x - xMin) / (xMax - xMin);
        return yMin + (yMax - yMin) * r;
    }
    /**
     * @param {Number} y
     * @returns {Number} x
     */
    getXfromY(y) {
        var yMax = Math.max(this.a.y, this.b.y);
        var yMin = Math.min(this.a.y, this.b.y);
        var xMax = Math.max(this.a.x, this.b.x);
        var xMin = Math.min(this.a.x, this.b.x);
        var r = (y - yMin) / (yMax - yMin);
        return xMin + (xMax - xMin) * r;
    }
    /**
     * 
     * @param {Line} line 
     * @returns {Boolean}
     */
    intersects(line) {
        if (this.isOn(line.a)) return true;
        return Math.round(Math.abs(this.a.x - this.b.x) / Math.abs(this.a.y - this.b.y) * 1e3) / 1e3 != Math.round(Math.abs(line.a.x - line.b.x) / Math.abs(line.a.y - line.b.y) * 1e3) / 1e3;
    }
    /**
     * 
     * @param {Line} line 
     * @returns {Boolean}
     */
    matches(line) {
        return Math.round(Math.abs(this.a.x - this.b.x) / Math.abs(this.a.y - this.b.y) * 1e3) / 1e3 == Math.round(Math.abs(line.a.x - line.b.x) / Math.abs(line.a.y - line.b.y) * 1e3) / 1e3 && this.isOn(line.a);
    }
    /**
     * 
     * @param {Line} line
     * @returns {Point}
     */
    getIntersect(line) {
        /**
         * @type {Point} 
         * @description Point directly above point a of line on this
         */
        var p1 = new Point(this.parent, line.a.x, this.getYfromX(line.a.x));
        var slope1 = (this.b.y - this.a.y) / (this.b.x - this.a.x);
        var slope2 = (line.b.y - line.a.y) / (line.b.x - line.a.x);
        var slopeDiff = slope1 - slope2
        var diff = p1.y - line.a.y;
        var xDiff = diff / slopeDiff;
        var x = line.a.x - xDiff;
        var y = line.getYfromX(x);
        return new Point(this.parent, x, y);
    }
    /**
     * 
     * @param {Point} point 
     * @return {Boolean}
     */
    isOn(point) {
        return this.getYfromX(point.x) === point.y;
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
    /**
     * 
     * @param {Point} point1 
     * @param {Point} point2 
     * @returns {Number}
     */
    static distance(point1, point2) {
        return Math.pow(Math.pow(point1.x - point2.x, 2) + Math.pow(point1.y - point2.y, 2), 1 / 2);
    }
    /**
     * 
     * @param {Point} point
     * @returns {Number}
     */
    distance(point) {
        return Math.pow(Math.pow(point.x - this.x, 2) + Math.pow(point.y - this.y, 2), 1 / 2);
    }
    /**
     *  
     * @param {Point} point 
     * @returns {Point}
     */
    reflectAbout(point) {
        var x = 2 * point.x - this.x;
        var y = 2 * point.y - this.y;
        return new Point(this.parent, x, y);
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
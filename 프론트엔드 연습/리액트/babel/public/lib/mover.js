'use strict';

var _createClass = function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; }();

function _possibleConstructorReturn(self, call) { if (!self) { throw new ReferenceError("this hasn't been initialised - super() hasn't been called"); } return call && (typeof call === "object" || typeof call === "function") ? call : self; }

function _inherits(subClass, superClass) { if (typeof superClass !== "function" && superClass !== null) { throw new TypeError("Super expression must either be null or a function, not " + typeof superClass); } subClass.prototype = Object.create(superClass && superClass.prototype, { constructor: { value: subClass, enumerable: false, writable: true, configurable: true } }); if (superClass) Object.setPrototypeOf ? Object.setPrototypeOf(subClass, superClass) : subClass.__proto__ = superClass; }

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

var Mover = function () {
    function Mover(color) {
        _classCallCheck(this, Mover);

        this.color = color;
        this.elem = document.createElement('div');
        this.elem.classList.add('mover', 'mover-' + color);
        this.elem.style.background = color;
        this.elem.addEventListener('click', this.go);
        document.body.appendChild(this.elem);

        this.go();
    }

    _createClass(Mover, [{
        key: 'go',
        value: function go(e) {
            var elem = void 0;
            if (e) {
                elem = e.currentTarget;
            } else {
                elem = this.elem;
            }
            var xPos = Math.random() * innerWidth * 0.9;
            var yPos = Math.random() * innerHeight * 0.9;
            elem.style.transform = 'translate3d(' + xPos + 'px, ' + yPos + 'px, 0)';
        }
    }, {
        key: 'getColor',
        get: function get() {
            return this.color;
        }
    }, {
        key: 'setColor',
        set: function set(newColor) {
            this.color = newColor;
            this.elem.style.background = newColor;
        }
    }], [{
        key: 'sayHello',
        value: function sayHello() {
            console.log('My name is Mover!');
        }
    }]);

    return Mover;
}();

var FastMover = function (_Mover) {
    _inherits(FastMover, _Mover);

    function FastMover(color) {
        _classCallCheck(this, FastMover);

        var _this = _possibleConstructorReturn(this, (FastMover.__proto__ || Object.getPrototypeOf(FastMover)).call(this, color));

        _this.elem.style.transitionDuration = '0.3s';
        return _this;
    }

    return FastMover;
}(Mover);
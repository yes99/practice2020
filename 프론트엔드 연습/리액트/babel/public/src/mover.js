class Mover {
    constructor(color) {
        this.color = color;
        this.elem = document.createElement('div');
        this.elem.classList.add('mover', `mover-${color}`);
        this.elem.style.background = color;
        this.elem.addEventListener('click', this.go);
        document.body.appendChild(this.elem);

        this.go();
    }

    go(e) {
        let elem;
        if (e) {
            elem = e.currentTarget;
        } else {
            elem = this.elem;
        }
        const xPos = Math.random() * innerWidth * 0.9;
        const yPos = Math.random() * innerHeight * 0.9;
        elem.style.transform = `translate3d(${xPos}px, ${yPos}px, 0)`;
    }

    get getColor() {
        return this.color;
    }

    set setColor(newColor) {
        this.color = newColor;
        this.elem.style.background = newColor;
    }

    static sayHello() {
        console.log(`My name is Mover!`);
    }
}

class FastMover extends Mover {
    constructor(color) {
        super(color);
        this.elem.style.transitionDuration = '0.3s';
    }
}
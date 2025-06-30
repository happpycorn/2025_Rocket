export function updateBoolCircles(boolArr) {
    const circles = document.querySelectorAll('.bool_circle');
    for (let i = 0; i < circles.length && i < boolArr.length; i++) {
        const circle = circles[i];
        circle.classList.toggle('bool_on', boolArr[i]);
        circle.classList.toggle('bool_off', !boolArr[i]);
    }
}

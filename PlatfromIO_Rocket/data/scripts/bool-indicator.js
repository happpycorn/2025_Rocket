export function updateBoolCircles(boolArr) {
    const circles = document.querySelectorAll('.bool_circle');
    let moved = boolArr.splice(11, 1)[0];  // 移除 index=11 的元素
    boolArr.splice(5, 0, moved);           // 在 index=5 插入這個元素
    for (let i = 0; i < circles.length && i < boolArr.length; i++) {
        const circle = circles[i];
        circle.classList.toggle('bool_on', boolArr[i]);
        circle.classList.toggle('bool_off', !boolArr[i]);
    }
}

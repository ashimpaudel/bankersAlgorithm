const navToggle = document.getElementById('nav-toggle');
const siteNav = document.getElementById('site-nav');
const yearElement = document.getElementById('year');

if (navToggle) {
    navToggle.addEventListener('click', () => {
        siteNav.classList.toggle('is-open');
    });
}

if (yearElement) {
    yearElement.textContent = new Date().getFullYear();
}

const navLinks = siteNav?.querySelectorAll('a');
navLinks?.forEach(link =>
    link.addEventListener('click', () => {
        siteNav.classList.remove('is-open');
    })
);

const contactForm = document.querySelector('.contact-form');
contactForm?.addEventListener('submit', event => {
    event.preventDefault();
    const form = event.currentTarget;
    form.classList.add('is-submitted');
    form.reset();
    alert("Thank you for contacting Nest Boy's Hostel! Our guardian team will reach out shortly.");
});

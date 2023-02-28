dbref.on("value", (snapshot) => {
    let value = snapshot.val();
    console.log(value);

    set_contact(value)
});

const update_val = (name, contact_1, contact_2, contact_3, vtype) => {
    firebase
        .database()
        .ref()
        .set({
            name: name,
            contact_1: contact_1,
            contact_2: contact_2,
            contact_3: contact_3,
            vtype: vtype
        })
        .then(() => {
            console.log(name);
        });
}


$('.contact_info').on('submit', (e) => {
    e.preventDefault()

    const { name, password, phone, contact_name_1, contact_name_2, contact_name_3, emergency_contact_1, emergency_contact_2, emergency_contact_3, vtype } = e.target
    SIGN_UP(name.value, password.value, phone.value, contact_name_1.value, contact_name_2.value, contact_name_3.value, emergency_contact_1.value, emergency_contact_2.value, emergency_contact_3.value, vtype.value)

    // SIGN_UP('croton', '007croton', "6096817869", "sathvik", "9502402016", '4')


})

$('.sign_in').on('submit', e => {
    e.preventDefault()

    const { phone_num, password } = e.target
    console.log(phone_num.value, password.value);
    SIGN_IN(phone_num.value, password.value)
    phone_num.value = ''
    password.value = ""
})



const set_contact = (phone) => {
    db.collection("userData")
        .get()
        .then((snapshot) => {
            snapshot.forEach((doc) => {
                data = doc.data()
                if (data.user_number == phone) {
                    console.log(data);
                    firebase
                        .database()
                        .ref()
                        .set({
                            phone: phone,
                            emergency_contact_1: data.emergency_contact_1,
                            emergency_contact_2: data.emergency_contact_2,
                            emergency_contact_3: data.emergency_contact_3,
                            name1: data.contact_name_1,
                            name2: data.contact_name_2,
                            name3: data.contact_name_3,
                            vtype: data.vtype

                        })
                        .then(() => {
                            console.log(name1, name2, name3);
                        });
                }
            })
        }).then(e => {
        })

}




const GET_DATA = (phone) => {

    db.collection("userData")
        .get()
        .then((snapshot) => {
            snapshot.forEach((doc) => {
                data = doc.data()
                console.log(phone);
                console.log(data.user_number);
                if (data.user_number == phone) {
                    console.log(data);

                    let html = `
                                <h1>Emergency Contact Details </h1>
                    <h4>Emergency Contact Name 1: ${data.contact_name_1}</h4>
                    <h4>Emergency Contact Number: ${data.emergency_contact_1}</h4>
                    <h4>Emergency Contact Name 2: ${data.contact_name_2}</h4>
                    <h4>Emergency Contact Number: ${data.emergency_contact_2}</h4>
                    <h4>Emergency Contact Name 3: ${data.contact_name_3}</h4>
                    <h4>Emergency Contact Number: ${data.emergency_contact_3}</h4>
                    <h4>Vehicle Type: ${data.vtype}</h4>

                    `
                    $('.details').html(html)
                    RENDER('details')
                }
            })
        }).then(e => {
        })

}


const SIGN_IN = (phone, password) => {

    db.collection("users")
        .get()
        .then((snapshot) => {
            snapshot.forEach((doc) => {

                let data = doc.data()
                console.log(phone, password);
                if (data.phone == phone && data.password == password) {
                    console.log("signed_in");
                    GET_DATA(phone);
                    set_contact(phone);

                }
            })
        }).then(e => {


        })

}




// GET_DATA()
// SIGN_IN('6096817869', '007croton')


const SIGN_UP = (name, password, phone, contact_name_1, contact_name_2, contact_name_3, emergency_contact_1, emergency_contact_2, emergency_contact_3, vtype) => {
    db.collection("users")
        .add({
            name,
            password,
            phone
        }).then(e => {
            db.collection('userData').add({ contact_name_1, contact_name_2, contact_name_3, emergency_contact_1, emergency_contact_2, emergency_contact_3, vtype, user_number: phone })
        }).then(() => {
            RENDER('login')
        })

}

// SIGN_UP('croton', '007croton', "6096817869", "sathvik", "9502402016", '4')



const RENDER = (page) => {
    switch (page) {
        case "login":

            $('.signup').addClass('d-none')
            $('.details').addClass('d-none')
            $('.login').removeClass('d-none')

            break;
        case "signup":
            $('.login').addClass('d-none')
            $('.details').addClass('d-none')
            $('.signup').removeClass('d-none')
            break;
        case "details":
            $('.login').addClass('d-none')
            $('.signup').addClass('d-none')
            $('.details').removeClass('d-none')

            break



        default:
            break;
    }
}
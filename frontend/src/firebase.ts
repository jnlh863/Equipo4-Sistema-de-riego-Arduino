// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getFirestore } from "firebase/firestore";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
const firebaseConfig = {
  apiKey: "AIzaSyBhGWjM2IEoMMO0l_OujUsBJPHfjKqCH90",
  authDomain: "sistema-de-riego-24fc2.firebaseapp.com",
  databaseURL: "https://sistema-de-riego-24fc2-default-rtdb.firebaseio.com",
  projectId: "sistema-de-riego-24fc2",
  storageBucket: "sistema-de-riego-24fc2.appspot.com",
  messagingSenderId: "436871986259",
  appId: "1:436871986259:web:cca953517596beb6419aa6",
  measurementId: "G-GC312J9D04",
};

// Initialize Firebase
export const app = initializeApp(firebaseConfig);
export const db = getFirestore(app);

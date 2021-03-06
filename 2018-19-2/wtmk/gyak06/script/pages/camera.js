import { setDisplayMode } from "../navigation";

const name = "camera";

const displayModes = {
  default: {
    "#camera-video": true,
    "#camera-canvas": false,
    "#camera-location": false
  },
  editing: {
    "#camera-video": false,
    "#camera-canvas": true,
    "#camera-location": true
  }
};

function init() {
  // Ellenőrizzük, hogy a "mediaDevices" (kamera) elérhető-e
  if (!("mediaDevices" in navigator)) {
    alert("Camera API not supported");
  }

  // Ellenőrizzük, hogy a "geolocation" (helyzet) elérhető-e
  if (!("geolocation" in navigator)) {
    alert("Location API not supported");
  }

  const actions = document.querySelector("#camera-actions");
  const capture = document.querySelector("#camera-capture");
  const discard = document.querySelector("#camera-discard");
  const save = document.querySelector("#camera-save");
  const video = document.querySelector("#camera-video");
  const canvas = document.querySelector("#camera-canvas");

  const context = canvas.getContext("2d");
  M.FloatingActionButton.init(actions, {
    toolbarEnabled: true
  });

  navigator.mediaDevices
    .getUserMedia({ video: true }) // Elkérjük a kamera videóképét
    .then(function(stream) {
      // Ha megvan
      video.srcObject = stream; //
    })
    .catch(function(error) {
      console.error(error);
    });

  // Ha a gombra kattintunk
  capture.addEventListener("click", function() {
    // A videó képét a vászonra rajzoljuk
    canvas.width = video.videoWidth;
    canvas.height = video.videoHeight;
    context.drawImage(video, 0, 0, video.videoWidth, video.videoHeight);

    setDisplayMode(displayModes.editing);

    // Elkérem a jelenlegi helyzetet
    navigator.geolocation.getCurrentPosition(function(position) {
      // Ha megvan
      const lat = position.coords.latitude;
      const lon = position.coords.longitude;
      // Netes szolgáltatás, ami visszaadja a szükséges adatokat róla
      // Google helyett OpenStreetMap, mert ingyenes és nem kell hozzá kulcs, így egyszerűbb
      const url = `https://nominatim.openstreetmap.org/reverse?format=json&lat=${lat}&lon=${lon}`;

      // Hely elkérése a OpenStreetMap szervertől
      fetch(url)
        .then(function(response) {
          return response.json();
        })
        .then(function(json) {
          const location = document.querySelector("#camera-location");
          location.innerHTML = `${json.address.city}, ${json.address.country}`;
        });
    });
  });

  discard.addEventListener("click", function() {
    setDisplayMode(displayModes.default);
  });

  // Kép feltöltés
  save.addEventListener("click", function() {
    const imageData = canvas.toDataURL();
    // console.log(imageData);

    // generálunk egy fájlnevet
    const filename =
      Date.now() +
      Math.random()
        .toString()
        .slice(2, 9) +
      ".png";
    const storage = firebase.storage().ref(filename);
    const database = firebase.firestore().collection("images");

    const location = document.querySelector("#camera-location").textContent;

    storage
      .putString(imageData, "data_url", {
        customMetadata: { location: location }
      })
      // Sikeres volt a fájl feltöltés
      .then(function() {
        // Beszúrok az adatbázisba
        return database.add({
          storagePath: filename
        });
      })
      .then(function() {
        M.toast({ html: "Upload successful", classes: "green" });
        setDisplayMode(displayModes.default);
      })
      .catch(function() {
        M.toast({ html: "Upload failed", classes: "red" });
      });
  });
}

const html = `
<section data-page="camera">
  <h1>Camera</h1>
  
  <div id="camera-camera">
    <video id="camera-video" autoplay></video>
    <canvas id="camera-canvas"></canvas>
  </div>

  <div class="fixed-action-btn toolbar" id="camera-actions">
    <!-- Kép készítő gomb -->
    <a id="camera-capture" class="btn-floating btn-large red">
      <i class="large material-icons">camera</i>
    </a>
    <!-- Kész képet kezelő gombok -->
    <ul>
      <li>
        <a id="camera-save" class="green"><i class="material-icons">save</i></a>
      </li>
      <li>
        <a id="camera-discard" class="red"><i class="material-icons">delete</i></a>
      </li>
    </ul>
  </div>

  <span id="camera-location"></span>
</section>
`;

export const CAMERA = { name, displayModes, init, html };

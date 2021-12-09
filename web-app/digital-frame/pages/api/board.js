import axios from "axios";

export default async(req, res) => {
  const url = `http://pictureFrame.local/ping`;

  await axios
  .get(url)
  .then((data) => {
    console.log(data);
    res.status(200)
  })
  .catch(({ err }) => {
    res.status(400)
  })
}

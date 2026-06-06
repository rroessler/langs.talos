/// Node Modules
import * as os from 'node:os';
import * as fs from 'node:fs';
import * as path from 'node:path';

/// Talos Modules
import { Product } from '@/talos/product';
import { Settings } from '@/talos/settings';

/** Gets the LSP server executable. */
export namespace Executable {
    //  PROPERTIES  //

    /** Expected base locations available. */
    const m_locations = [
        // as well as a development path as well (eg: located against build outputs)
        path.resolve(__dirname, '..', 'bin', Product.executable),

        // prepare a valid location for the potential executable
        path.resolve(os.homedir(), '.talos', 'bin', Product.executable),
    ];

    //  PUBLIC METHODS  //

    /** Gets the executable name. */
    export const name = () => Product.executable;

    /** Resolves a desired executable. */
    export const resolve = () => {
        const user = Settings.get('server.executablePath').trim();
        const locations = user ? [user].concat(m_locations) : m_locations;
        return locations.filter((location) => fs.existsSync(location)).at(0);
    };
}
